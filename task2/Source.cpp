#include <iostream>
#include "landmarksBasic.h"
#include "landmarksBFS.h"
#include<chrono>
using namespace std::chrono;

int main() {
    try {
        auto start = high_resolution_clock::now();
        UndirectedGraph graph("datasets/undirected/ca-coauthors-dblp.txt");
        LandmarksBFS basic(graph, "best-coverage", 300, 1000);
        auto stop = high_resolution_clock::now();
        std::cout << "File loaded for: " << double(duration_cast<microseconds>(stop - start).count()) / 1e6 << "s\n";
        
        double mae = 0;
        double mape = 0;
        int n = 500;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<uint32> dist(0, graph.vertixNumber() - 1);
        uint32 u;
        uint32 v;
        start = high_resolution_clock::now();
        for (int i = 0; i < n; ++i) {
            u = dist(gen);
            v = dist(gen);
            uint32 r1 = basic.computeApproximateDistance(graph, u, v, true);
            uint32 r2 = graph.findShortestPath(u, v, true);
            mae += (r1 - r2);
            mape += double(r1 - r2) / r2;
        }
        stop = high_resolution_clock::now();
        std::cout << "Loop worked for: " << double(duration_cast<microseconds>(stop - start).count()) / 1e6 << "s\n";
        std::cout << "MAE: " << mae / n << '\n' << "MAPE: " << mape / n ;
    }
    catch (std::exception& ex) {
        std::cout << ex.what();
    }
    
    return 0;
}