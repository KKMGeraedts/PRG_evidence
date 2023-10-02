#include <chrono>
#include <iostream>

using namespace std;

class Timer {
    public: Timer() {
        m_StartTimepoint = chrono::high_resolution_clock::now();
    }

    // When deconstructed
    ~Timer() {
        stop();
    }

    void stop() {
        auto endTimePoint = chrono::high_resolution_clock::now();

        auto start = chrono::time_point_cast<chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        auto end = chrono::time_point_cast<chrono::microseconds>(endTimePoint).time_since_epoch().count();
        
        auto duration = end - start;
        double ms = duration * 0.001;

        cout << "Duration: " << duration << "us (" << ms << " ms)\n";
    }

    private: chrono::time_point<chrono::high_resolution_clock> m_StartTimepoint;
};