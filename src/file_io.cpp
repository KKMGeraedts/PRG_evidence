#include "file_io.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

std::vector<std::vector<double>> read_wolffcpp_ising_data(const std::string &T, int L) {
    std::vector<std::vector<double>> data;
    std::string filename = "../../input/2dising_L=" + std::to_string(L) + "_T=" + T + ".txt";
    std::ifstream file(filename);
    
    if (!file) {
        std::cout << "File " << filename << " not found!" << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<double> row;
        std::istringstream iss(line);
        double value;
        while (iss >> value) {
            row.push_back(value);
        }
        data.push_back(row);
    }

    return data;
}


void write_pairs_to_file(const vector<pair<int, int>> &pairs, const string &filename) {
    ofstream file("../../data/" + filename);
    if (file.is_open()) {
        for (const auto &p : pairs) {
            file << p.first << ", " << p.second << "\n";
        }
        file.close();
    } else {
        cout << "Unable to open file: " << filename << "\n";
    }
}

void write_data_to_file(const vector<vector<double>> &data, const string &filename) {
    ofstream file("../../data/" + filename);
    if (file.is_open()) {
        for (const auto &row : data) {
            for (double val : row) {
                file << val << " ";
            }
            file << "\n";
        }
        file.close();
    } else {
        cout << "Unable to open file: " << filename << "\n";
    }
}

