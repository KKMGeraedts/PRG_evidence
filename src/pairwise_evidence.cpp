#include <vector>
#include <map>
#include <cmath>
#include "pairwise_evidence.h"

using namespace std;

vector<double> compute_pairwise_evidence(const vector<vector<double>> &x) {
    vector<double> pairwise_evidence;
    for (int i = 0; i < x.size(); ++i) {
        for (int j = i + 1; j < x.size(); ++j) {
            vector<vector<double>> pair(2, vector<double>(x[0].size(), 2));
            pair[0] = x[i];
            pair[1] = x[j];

            map<vector<double>, int> counts;
            for (const auto &val : pair) {
                counts[val]++;
            }

            double log_evidence = 0.0;
            for (const auto &[val, count] : counts) {
                log_evidence += lgamma(count + 0.5);
            }

            pairwise_evidence.push_back(log_evidence);
        }
    }
    return pairwise_evidence;
}

