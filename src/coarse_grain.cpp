#include <vector>
#include "coarse_grain.h"
#include "pairwise_evidence.h"
#include "helper_functions.h"
#include "file_io.h"

using namespace std;

void coarse_grain_process(vector<vector<double>> &x) {
    int iteration = 0;

    while (x.size() > 1) {
        vector<vector<double>> x_new(x.size() / 2, vector<double>(x[0].size(), 0)); // Initialize x_new
        vector<double> pairwise_evidence = compute_pairwise_evidence(x);
        vector<pair<int, int>> pairs;

        int pair_index = 0;
        while (!pairwise_evidence.empty()) {
            pair<int, int> max_pair = get_max_pair_and_invalidate(pairwise_evidence, pairs);

            // Compute average of max pair and store in x_new
            for (size_t k = 0; k < x[0].size(); ++k) {
                x_new[pair_index][k] = (x[max_pair.first][k] + x[max_pair.second][k]) / 2.0;
            }

            pair_index++; // Move to the next pair in x_new
        }

        // Write pairs and data to file
	string iter_str = to_string(iteration);
        write_pairs_to_file(pairs, "pairs_" + iter_str + ".txt");
        write_data_to_file(x, "data_" + iter_str + ".txt");

        x = x_new; // Prepare for the next iteration
        iteration++; // Increase iteration counter
    }
}

