#pragma once

#include <vector>
#include <string>

using namespace std;

vector<vector<double>> read_wolffcpp_ising_data(const string &T, int L);
void write_pairs_to_file(const vector<pair<int, int>> &pairs, const string &filename);
void write_data_to_file(const vector<vector<double>> &data, const string &filename);

