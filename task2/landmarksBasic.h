#ifndef LANDMARKSBASICALGORITHM
#define LANDMARKSBASICALGORITHM


#include "landmarksSelection.h"
#include <omp.h>


class LandmarksBasic {
	std::vector<std::vector<uint32>> distances_;

	void BFSPrecompute_(const UndirectedGraph& graph, uint32 s, uint32 index) {
		distances_[index][s] = 0;
		std::queue<uint32> q;
		q.push(s);
		uint32 v;
		while (!q.empty()) {
			v = q.front();
			q.pop();
			for (auto u : graph.internalAdj(v)) {
				if (distances_[index][u] == UndirectedGraph::maxVertixNumber) {
					distances_[index][u] = distances_[index][v] + 1;
					q.push(u);
				}
			}
		}
	}

public:
	/*
	* @param[in] graph: contains graph, which is considered as undirected
	* @param[in] landmarkSelectionMethod: options - LandmarksSelection::availableSelectionMethods
	* @param[in] k: desired number of landmarks
	* @param[in] M: desired number of shortest paths will be collected, specify only if best-coverage method selected
	*/
	LandmarksBasic(const UndirectedGraph& graph, const std::string& landmarkSelectionMethod, uint32 k, uint32 M = 0) : 
		distances_(k, std::vector<uint32>(graph.vertixNumber(), UndirectedGraph::maxVertixNumber)) {
		
		std::vector<uint32> landmarks;
		LandmarksSelection::chooseMethodByString(graph, landmarks, landmarkSelectionMethod, k, M);

		omp_set_num_threads(omp_get_max_threads());
#pragma omp parallel for
		for (int64 i = 0; i < landmarks.size(); ++i) {
			BFSPrecompute_(graph, landmarks[i], i);
		}
	}

	uint32 computeApproximateDistance(const UndirectedGraph& graph, uint64 s, uint64 t) const {
		if (s == t) {
			return 0;
		}
		s = graph.internalVertixName(s);
		t = graph.internalVertixName(t);
		if (s == UndirectedGraph::maxVertixNumber || t == UndirectedGraph::maxVertixNumber) {
			throw std::exception(std::string("One of the vertices (s, t) doesn't exist.").c_str());
		}

		uint32 minDist = UndirectedGraph::maxVertixNumber;
		uint32 currentDist;
		for (uint32 i = 0; i < distances_.size(); ++i) {
			if (distances_[i][s] < UndirectedGraph::maxVertixNumber && 
				distances_[i][t] < UndirectedGraph::maxVertixNumber) {
				currentDist = distances_[i][s] + distances_[i][t];
				if (minDist > currentDist) {
					minDist = currentDist;
				}
			}
		}
		return minDist;
	}
};


#endif

