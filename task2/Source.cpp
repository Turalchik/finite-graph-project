#include <iostream>
#include "landmarksBasic.h"
#include "landmarksBFS.h"


int main() {
    try {
        UndirectedGraph graph("test_sample.txt");
        LandmarksBFS basic(graph, "best-coverage", 4, 2);
        std::cout << basic.computeApproximateDistance(graph, 5994, 5) << '\n';
        std::cout << graph.findShortestPath(5, 5994);
    }
    catch (std::exception& ex) {
        std::cout << ex.what();
    }
    
    return 0;
}
