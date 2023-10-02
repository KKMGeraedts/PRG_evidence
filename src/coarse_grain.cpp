#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "coarse_grain.h"
#include "pairwise_evidence.h"
#include "helper_functions.h"
#include "file_io.h"
#include <bitset>
#include <unordered_map>
#include "constants.h"

using namespace std;

void coarse_grain_process(const vector<vector<int>> &x_original, int rg_iterations) {


    // Store binary data in a unordered map<bitset, int> (<state, count>)
    using Datapoint = std::bitset<MAX_NUM_VARIABLES>;

    std::unordered_map<Datapoint, int> x_map_binary;

    // Assuming x has shape (# of variables, # of datapoints)
    for (size_t j = 0; j < x_original[0].size(); ++j) {
        Datapoint binaryRow; // Create a bitset for each row

        for (size_t i = 0; i < x_original.size(); ++i) {
            // Data will be binary and in the {0, 1} basis
            binaryRow[i] = (x_original[i][j] == 1);
        }

        x_map_binary[binaryRow]++; // Store the binary row
    }
    
    // Initialize clusters (this contains the indices from 0, x.size())
    vector<vector<int>> clusters(x_original.size());
    for (int i = 0; i < x_original.size(); ++i) {
        clusters[i] = {i};
    }

    // Store dataset in a copy: 'x', this time as a vector<vector<double>>
    vector<vector<double>> x(x_original.size(), vector<double>(x_original[0].size()));

    for (size_t i = 0; i < x_original.size(); ++i) {
        transform(x_original[i].begin(), x_original[i].end(), x[i].begin(), [](int value) {
            return static_cast<double>(value);
        });
    }

    
    // Initialize
    int iteration = 0;
    vector<vector<int>> new_clusters;
    int pair_index;
    int stop_criterion;
    vector<double> evidence_of_merged_clusters;
    vector<pair<int, int>> pairs;
    vector<double> pairwise_evidence;
    string iter_str;
    vector<int> new_cluster;

    while (rg_iterations != 0) {
        // Initialize x_coarse
        vector<vector<double>> x_coarse(x.size() / 2, vector<double>(x[0].size(), 0));
        
        // Reset some variables
        pairs.clear();
        pairwise_evidence.clear();
        evidence_of_merged_clusters.clear();
        pair_index = 0;

        // Compute pairwise evidence
        cout << "Computing pairwise evidence..." << endl;
        pairwise_evidence = compute_pairwise_evidence(x_map_binary, clusters, pairs);
        cout << "Finished computing pairwise evidence." << endl;
        
		// // Print pairs
        // for (size_t i = 0; i < pairwise_evidence.size(); ++i) {
        //     cout << "Pair: (" << pairs[i].first << ", " << pairs[i].second << "), ";
        //     cout << "Evidence: " << pairwise_evidence[i] << endl;
        // }

        // Store pairwise evidence
        iter_str = to_string(iteration);
        write_evidences_to_file(pairwise_evidence, "evidence_" + iter_str + ".txt");

	    // Coarse-grain by pairs
        cout << "Merging pairs..." << endl;
        stop_criterion = clusters.size() / 2;
        while (pair_index != stop_criterion) {

            // Find index of pair with largest log evidence
            size_t index_max_pair = get_max_pair_and_invalidate(pairwise_evidence, pairs, evidence_of_merged_clusters);

            // Retrive pair
            pair<int, int> max_pair = pairs[index_max_pair];

            // Compute average of max pair and store in x_coarse
            for (size_t k = 0; k < x[0].size(); ++k) {
                x_coarse[pair_index][k] = (x[max_pair.first][k] + x[max_pair.second][k]) / 2.0;
            }

            pair_index++; // Move to the next pair in x_coarse
            
            // Merge old clusters
            new_cluster.clear();
            for (auto index : clusters[max_pair.first]) {
                // cout << "index: " << index << endl;
                new_cluster.emplace_back(index);
            }
            for (auto index : clusters[max_pair.second]) {
                new_cluster.emplace_back(index);
                // cout << "index: " << index << endl;
            }

            // Print progres
            if (pair_index % 100 == 0) {
                cout << 100 * pair_index / stop_criterion << " %\n";
            }

            // // Print new cluster
            // cout << "new cluster: ";
            // for (int i = 0; i < 2; ++i){
            //     cout << new_cluster[i];
            // }
            // cout << endl;

            // add new merged cluster to new_clusters
            new_clusters.push_back(new_cluster);
        }
        cout << "Finished merging pairs." << endl;


        // Print new clusters
        // cout << "new clusters :" << endl;
        // for (int i = 0; i < new_clusters.size(); ++i){
        //     for (int j = 0; j < new_clusters[0].size(); ++j){
        //         cout << new_clusters[i][j];
        //     }
        //     cout << endl;
        // }

        // Write clusters, pairs and data to file
        write_merged_evidences_to_file(evidence_of_merged_clusters, "merged_evidences_" + iter_str + ".txt");
        write_clusters_to_file(new_clusters, "clusters_" + iter_str + ".txt");
        write_pairs_to_file(pairs, "pairs_" + iter_str + ".txt");
        write_data_to_file(x_coarse, "data_" + iter_str + ".txt");

        x = x_coarse; // Prepare for the next iteration
        iteration++; // Increase iteration counter
	    rg_iterations -= 1;
        
        cout << "Finished iteration: " << iteration << endl;
        
        // Update clusters
        clusters = new_clusters;
        new_clusters.clear();
    }

    // Print final clusters
    cout << endl << "Finished PRG procedure!" << endl;
    cout << "Final clustering: " << endl;
    for (int i = 0; i < clusters.size(); ++i){
        cout << "Cluster " << i << ":\n"; 
        for (int j = 0; j < clusters[0].size(); ++j){
            cout << clusters[i][j] << ",";
        }
        cout << endl;
    }
	
}

