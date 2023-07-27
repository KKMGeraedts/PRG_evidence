#include "coarse_grain.h"
#include "file_io.h"

using namespace std;

int main() {
    std::string T = "3.0";
    int L = 40;
    vector<vector<double>> x = read_wolffcpp_ising_data(T, L);

    coarse_grain_process(x);

    return 0;
}

