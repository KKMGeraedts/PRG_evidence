#pragma once

#include <vector>
#include <string>

using namespace std;

string check_file_extension(const string &filename);
vector<vector<int>> read_txt_file(const string &filename);
vector<vector<int>> read_dat_file(const string &filename);
void write_merged_evidences_to_file(const vector<double> &merged_evidences, const string &filename);
void write_pairs_to_file(const vector<pair<int, int>> &pairs, const string &filename);
void write_data_to_file(const vector<vector<double>> &data, const string &filename);
void write_evidences_to_file(const vector<double> &pairwise_evidence, const string &filename);
void write_clusters_to_file(const vector<vector<int>> &clusters, const string &filename);
void clearFolder(const std::string& folderPath);
