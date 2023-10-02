#include <vector>
#include <algorithm>
#include <limits>
#include "helper_functions.h"
#include <iostream>

using namespace std;

size_t get_max_pair_and_invalidate(
    vector<double> &pairwise_evidence,
    vector<pair<int, int>> &pairs,
    vector<double> &evidence_of_merged_clusters
    ) {
    /* Find the maximum value in the pariwise evidence matrix and check it for validity. */

    // Find largest element
    auto max_evidence = max_element(pairwise_evidence.begin(), pairwise_evidence.end());

    // Get index of the maximum evidence
    size_t index = distance(pairwise_evidence.begin(), max_evidence);

    // Store evidence in list
    evidence_of_merged_clusters.push_back(pairwise_evidence[index]);

    // Get corresponding pair of variables
    pair<int, int> max_pair = pairs[index];
    
    // Print statistics
    // cout << "max_iter: " << *max_evidence 
    //       << ", index: " << index 
    //       << ", max_pair: (" << max_pair.first << "," << max_pair.second << ")" 
    //       << endl;

    // Invalidate all pairs involving i or j
    for (size_t k = 0; k < pairs.size(); ++k) {
        if (pairs[k].first == max_pair.first || pairs[k].second == max_pair.first || pairs[k].first == max_pair.second || pairs[k].second == max_pair.second) {
            pairwise_evidence[k] = -numeric_limits<double>::infinity();
        }
    }

    return index;
}

void reshape_to_matrix(vector<vector<double>> &x, int dim1, int dim2){
    vector<vector<double>> reshaped(dim1, vector<double>(dim2));
 
    for (int i = 0; i < x.size(); ++i) {
        for (int j = 0; j < x[0].size(); ++j) {
	    int new_i = (i * x[0].size() + j) / dim2;   // calculate new row index
	    int new_j = (i * x[0].size() + j) % dim2;   // calculate new column index
	    reshaped[new_i][new_j] = x[i][j];
        }
    }
    x = reshaped;
}

void reshape_if_necessary(vector<vector<double>> &x){
    if(x.size() == 1 || x[0].size() == 1){
        cout << "Warning: x is one-dimensional with shape: (" << x.size() << ", " << x[0].size() << ")." << endl;
        cout << "Please provide the dimensions to reshape to a matrix: " << endl;

        int dim1, dim2;
        cout << "First dimension: ";
        cin >> dim1;
        cout << "Second dimension: ";
        cin >> dim2;
        
        if(dim1 * dim2 != x.size() * x[0].size()) {
            cout << "Error: Provided dimensions do not match the total number of elements. Please check the dimensions." << endl;
        } else {
            reshape_to_matrix(x, dim1, dim2);
        }
    }
    else if (x.size() != x[0].size()) {
        cout << "Warning: x is not a square matrix with shape: (" << x.size() << ", " << x[0].size() << ")." << endl;
        cout << "Please provide the dimensions to reshape to a square matrix: " << endl;

        int dim;
        cout << "Dimension: ";
        cin >> dim;
        
        if(dim * dim != x.size() * x[0].size()) {
            cout << "Error: Provided dimension does not match the total number of elements. Please check the dimension." << endl;
        } else {
            reshape_to_matrix(x, dim, dim);
        }
    }
}

