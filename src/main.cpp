#include "coarse_grain.h"
#include "file_io.h"
#include <iostream>

using namespace std;

int main() {
    std::string T = "2.0";
    int L = 16;
    
    // Load data
    std::cout << "Loading data.." << std::endl;
    vector<vector<double>> x = read_wolffcpp_ising_data(T, L);
    std::cout << "Data loaded." << std::endl;
    
    // Start coarse-graining procedure
    std::cout << "Started coarse-graining procedure..." << std::endl;
    coarse_grain_process(x);
    std::cout << "Finished coarse-graining procedure." << std::endl;

    return 0;
}

