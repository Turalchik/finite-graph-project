#ifndef LANDMARKSBFSALGORITHM
#define LANDMARKSBFSALGORITHM

#include "landmarksSelection.h"
#include <omp.h>

class LandmarksBFS {
	std::vector<std::vector<uint32>> SPTs_;
	std::vector<uint32> landmarks_;

	void BFSPrecompute_(const UndirectedGraph& graph, uint32 s, uint32 index) {
		std::queue<uint32> q;
		q.push(s);
		uint32 v;
		while (!q.empty()) {
			v = q.front();
			q.pop();
			for (auto u : graph.internalAdj(v)) {
				if (SPTs_[index][u] == UndirectedGraph::maxVertixNumber) {
					SPTs_[index][u] = v;
					q.push(u);
				}
			}
		}
	}

	uint32 BFSCompute_(const UndirectedGraph& graph, std::vector<uint32>& dist, uint32 s, uint32 t) const {
		dist[s] = 0;
		std::queue<uint32> q;
		q.push(s);
		uint32 v;
		while (!q.empty()) {
			v = q.front();
			q.pop();
			for (auto u : graph.internalAdj(v)) {
				if (dist[u] == UndirectedGraph::maxVertixNumber) {
					dist[u] = dist[v] + 1;
					q.push(u);
				}
				if (u == t) {
					return dist[u];
				}
			}
		}
		return dist[t];
	}

	void fillWithPath_(std::unordered_set<uint32>& pathVertices, uint64 w, uint32 index) const {
		if (SPTs_[index][w] == UndirectedGraph::maxVertixNumber) {
			return;
		}
		uint32 v = w;
		while (v != landmarks_[index]) {
			v = SPTs_[index][v];
			pathVertices.emplace(v);
		}
	}

public:
	/*
	* @param[in] graph: contains graph, which is considered as undirected
	* @param[in] landmarkSelectionMethod: options - LandmarksSelection::availableSelectionMethods
	* @param[in] k: desired number of landmarks, k = min(k, graph.vertixNumber());
	* @param[in] M: desired number of shortest paths will be collected, specify only if best-coverage method selected
	*/
	LandmarksBFS(const UndirectedGraph& graph, const std::string& landmarkSelectionMethod, uint32 k, uint32 M = 0) :
		SPTs_(k, std::vector<uint32>(graph.vertixNumber(), UndirectedGraph::maxVertixNumber)) {

		LandmarksSelection::chooseMethodByString(graph, landmarks_, landmarkSelectionMethod, k, M);

		omp_set_num_threads(omp_get_max_threads());
#pragma omp parallel for
		for (int64 i = 0; i < landmarks_.size(); ++i) {
			BFSPrecompute_(graph, landmarks_[i], i);
		}
	}

	uint32 computeApproximateDistance(const UndirectedGraph& graph, uint64 s, uint64 t, bool internalVertixRepresentationPassed = false) const {
		if (s == t) {
			return 0;
		}
		if (!internalVertixRepresentationPassed) {
			s = graph.internalVertixName(s);
			t = graph.internalVertixName(t);
			if (s == UndirectedGraph::maxVertixNumber || t == UndirectedGraph::maxVertixNumber) {
				throw std::exception(std::string("One of the vertices (s, t) doesn't exist.").c_str());
			}
		}
		else {
			if (s >= graph.vertixNumber() || t >= graph.vertixNumber()) {
				throw std::exception(std::string("One of the vertices (s, t) doesn't exist.").c_str());
			}
		}

		std::unordered_set<uint32> pathVertices;
		pathVertices.emplace(s);
		pathVertices.emplace(t);
		for (uint32 i = 0; i < landmarks_.size(); ++i) {
			fillWithPath_(pathVertices, s, i);
			fillWithPath_(pathVertices, t, i);
		}

		std::vector<uint32> dist(graph.vertixNumber(), 0);
		for (auto v : pathVertices) {
			dist[v] = UndirectedGraph::maxVertixNumber;
		}
		return BFSCompute_(graph, dist, s, t);
	}
};


#endif

