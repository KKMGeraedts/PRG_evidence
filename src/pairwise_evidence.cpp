#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#include "pairwise_evidence.h"
#include <sstream>
#include <string>
#include <algorithm>
#include "sample_binary_vars.h"
#include "constants.h"
#include <bitset>
#include <unordered_map>
	
using namespace std;

string vecToString(const vector<double>& v) {
    ostringstream oss;
    for (auto val : v) {
        oss << val << " ";
    }
    string str = oss.str();
    return str.substr(0, str.length()-1);  // remove trailing space
}

map<string, int> count_states(const std::unordered_map<std::bitset<MAX_NUM_VARIABLES>, int> &x, const vector<int> &cluster){
    map<string, int> counts;
    /* Create the distribution of states for a given cluster. Cluster should include a vector of 
    variable indices that are included in the cluster. 'x' should be the orignal binary data.*/

    string cluster_state;
    for (const auto &[state, count]: x){
        cluster_state = "";
        for (auto c: cluster) {
            cluster_state += to_string(state[c]);
        }
        counts[cluster_state] += count;
    }
    return counts;
}

vector<double> compute_pairwise_evidence(std::unordered_map<std::bitset<MAX_NUM_VARIABLES>, int> &x, vector<vector<int>> &clusters, vector<pair<int, int>> &pairs) {
    /* This function compute the log evidence of binary values in the {+1, -1} basis. The log evidence is computed for all
    possible pairings in the given vector clusters. 

    Return: 
        pairwise_evidence - a vector containing the log evidence for all possible pairings.
    */
    
    vector<double> pairwise_evidence;
    vector<int> new_cluster;
    double log_evidence;
    map<string, int> counts;

    // Sample binary spins
    //vector<vector<int>> x_binary = sample_binary_variables(x);

    // Compute pairwise evidence for all possible pairings
    for (int i = 0; i < clusters.size(); ++i) {
        for (int j = i + 1; j < clusters.size(); ++j) {
	    
            // Store cluster_i into a new cluster
            new_cluster = clusters[i];

            // Append variables in cluster_j to new_cluster
            new_cluster.insert(new_cluster.end(), clusters[j].begin(), clusters[j].end());

            // Count occurence of states
            counts = count_states(x, new_cluster);

	        // Compute log evidence
            log_evidence = -0.5 * log(M_PI) * x.size();
            // cout << "Count of states for pair (" << i << ", " << j << ")" << endl;
            for (const auto &[state, count] : counts) {
                log_evidence += lgamma(count + 0.5);
            }

	        // Store evidence and corresponding cluster index (i,j)
            pairwise_evidence.push_back(log_evidence);
            pairs.push_back({i, j});
        }

        // Print progress
        if (i % 10 == 0) {
            cout << i << "/" << clusters.size() << endl;
        }
    }
    return pairwise_evidence;
}

