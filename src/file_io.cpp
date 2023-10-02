#include "file_io.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

std::string check_file_extension(const std::string &filename) {
    // Find the position of the last dot (.) in the filename
    size_t dotPosition = filename.find_last_of('.');

    // Check if a dot was found and if it's not the last character in the filename
    if (dotPosition != std::string::npos && dotPosition < filename.length() - 1) {
        // Extract and return the extension (substring after the last dot)
        return filename.substr(dotPosition + 1);
    }

    // If no dot or it's the last character, return an empty string to indicate no extension found
    return "";
}

vector<vector<int>> read_txt_file(const string &filename) {
    /* Read data from a text file. Datapoints are seperated by line breaks and variables are separated
    by white spaces. The input data should be binary! 

    Return: The returned data matrix will have shape (number of variables, number of datapoints).
    */

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "File " << filename << " not found!\n";
        return {};
    }

    vector<vector<int>> transposedData; // Initialize as empty

    string line;
    if (getline(file, line)) {
        istringstream iss(line);
        int val;
        while (iss >> val) {
            transposedData.push_back({val}); // Each value becomes a new row
        }
    }

    while (getline(file, line)) {
        istringstream iss(line);
        size_t col = 0;
        int val;
        while (iss >> val && col < transposedData.size()) {
            transposedData[col++].push_back(val); // Append to existing rows
        }
    }

    return transposedData;
}

vector<vector<int>> read_dat_file(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File " << filename << " not found!" << endl;
        return {};
    }

    vector<vector<int>> data;

    string line;
    cout << endl;
    while (getline(file, line)) {
        vector<int> row;

        for (char c : line) {
            int val = c - '0';
            row.push_back(val);
        }

        // Transpose: Add the row to columns instead of rows
        for (size_t i = 0; i < row.size(); ++i) {
            if (i >= data.size()) {
                data.push_back({});
            }
            data[i].push_back(row[i]);
        }
    }

    return data;
}

void write_pairs_to_file(const vector<pair<int, int>> &pairs, const string &filename) {
    ofstream file("../data/pairs/" + filename);
    if (file.is_open()) {
        for (const auto &p : pairs) {
            file << p.first << ", " << p.second << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}

void write_data_to_file(const vector<vector<double>> &data, const string &filename) {
    ofstream file("../data/activity/" + filename);
    if (file.is_open()) {
        for (const auto &row : data) {
            for (double val : row) {
                file << val << " ";
            }
            file << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}

void write_evidences_to_file(const vector<double> &pairwise_evidence, const string &filename) {
    ofstream file("../data/evidence/" + filename);

    if (file.is_open()) {
        for (double evidence : pairwise_evidence) {
            file << evidence << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}

void write_merged_evidences_to_file(const vector<double> &merged_evidences, const string &filename) {
    ofstream file("../data/merged_evidences/" + filename);

    if (file.is_open()) {
        for (double evidence : merged_evidences) {
            file << evidence << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}

void write_clusters_to_file(const vector<vector<int>> &clusters, const string &filename) {
    ofstream file("../data/clusters/" + filename);

    if (file.is_open()) {
        for (const auto &row : clusters) {
            for (int val : row) {
                file << val << " ";
            }
            file << endl;
        }
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}

void clearFolder(const std::string& folderPath) {
    try {
        // Check if the folder exists
        if (fs::exists(folderPath) && fs::is_directory(folderPath)) {
            // Iterate over the contents of the folder
            for (const auto& entry : fs::directory_iterator(folderPath)) {
                // Remove each file or subfolder
                fs::remove_all(entry.path());
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error clearing folder: " << ex.what() << std::endl;
    }
}