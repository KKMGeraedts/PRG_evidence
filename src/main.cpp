#include "coarse_grain.h"
#include "file_io.h"
#include <iostream>
#include "helper_functions.h"
#include <vector>
#include "timer.cpp"
#include <bitset>
#include <unordered_map>
#include "constants.h"

using namespace std;

int main(int argc, char *argv[]) {
    // Check if the filename is provided
    if(argc < 3) {
        std::cerr << "Usage: ./.. filename rg_iterations\n";
        return 1;
    }
    
    // Filename
    string filename = argv[1];
    
    // RG iterations
    int rg_iterations = stoi(argv[2]);

    // Load data
    cout << "Loading data from " << filename << endl;
    vector<vector<int>> x;

    // Check file extension
    string extension = check_file_extension(filename);
    
    // Only able to read .dat and .txt files
    if (extension == "dat") {
        x = read_dat_file(filename); // shape = (variables, datapoints)
    } else if (extension == "txt") {
        x = read_txt_file(filename); // shape = (variables, datapoints)
    } else {
        cout << "Not able to load file with extension: " << extension << endl;
        return -1;
    }
    cout << "Data loaded." << endl;

    // Reshape if necessary
    // reshape_if_necessary(x);

    // // Print the loaded data
    // cout << "Loaded data:" << endl;
    // for (size_t i = 0; i < x.size(); ++i) {
    //     for (size_t j = 0; j < x[i].size(); ++j) {
    //         cout << x[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // Paths to the folders that should be cleared
    std::string foldersToClear[] = {
        "../data/activity/",
        "../data/clusters/",
        "../data/evidence/",
        "../data/merged_evidences/",
        "../data/pairs/"
    };

    // Before procedure start clear folders containing old data
    for (const std::string& folderPath : foldersToClear) {
        clearFolder(folderPath);
    }

    // Start coarse-graining procedure
    cout << "Started coarse-graining procedure..." << endl;

    Timer timer;
    coarse_grain_process(x, rg_iterations);

    return 0;
}

