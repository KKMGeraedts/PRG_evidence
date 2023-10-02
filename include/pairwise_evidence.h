#include <vector>
#include <bitset>
#include <unordered_map>
#include "constants.h"

using namespace std;

vector<double> compute_pairwise_evidence(std::unordered_map<std::bitset<MAX_NUM_VARIABLES>, int> &x, vector<vector<int>> &old_clusters, vector<pair<int, int>> &pairs);
