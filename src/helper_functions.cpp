#include <vector>
#include <algorithm>
#include <limits>
#include "helper_functions.h"

using namespace std;

pair<int, int> get_max_pair_and_invalidate(vector<double> &pairwise_evidence, vector<pair<int, int>> &pairs) {
    auto max_iter = max_element(pairwise_evidence.begin(), pairwise_evidence.end());
    size_t index = distance(pairwise_evidence.begin(), max_iter);
    pair<int, int> max_pair = pairs[index];

    // Invalidate all pairs involving i or j
    for (size_t k = 0; k < pairs.size(); ++k) {
        if (pairs[k].first == max_pair.first || pairs[k].second == max_pair.first || pairs[k].first == max_pair.second || pairs[k].second == max_pair.second) {
            pairwise_evidence[k] = -std::numeric_limits<double>::infinity();
        }
    }

    return max_pair;
}

