#include <vector>
#include <random>

using namespace std;

vector<vector<int>> sample_binary_variables(const vector<vector<double>>& x) {
    // Initialize a random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(0.0, 1.0);

    // Initialize the result vector with the same shape as x
    vector<vector<int>> x_sample(x.size(), vector<int>(x[0].size(), 0));

    // Sample binary variables based on the probabilities in x
    for (size_t i = 0; i < x.size(); ++i) {
        for (size_t j = 0; j < x[i].size(); ++j) {
            double shifted_prob = (x[i][j] + 1.0) / 2.0; // This only works for {+1, -1} basis
            if (dist(gen) < shifted_prob) {
                x_sample[i][j] = 1; // Set to +1
            } else {
                x_sample[i][j] = -1; // Set to -1
            }
        }
    }

    return x_sample;
}
