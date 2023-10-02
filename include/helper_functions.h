#include <vector>

using namespace std;

size_t get_max_pair_and_invalidate(
    vector<double> &pairwise_evidence,
    vector<pair<int, int>> &pairs, 
    vector<double> &evidence_of_merged_clusters);
void reshape_to_matrix(vector<vector<double>> &x, int dim1, int dim2);
void reshape_if_necessary(vector<vector<double>> &x);
