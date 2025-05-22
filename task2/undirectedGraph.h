#ifndef UNDIRECTEDGRAPHDATASTRUCTURE
#define UNDIRECTEDGRAPHDATASTRUCTURE

typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <queue>

class UndirectedGraph {
	std::vector<std::vector<uint32>> graph_;
	std::unordered_map<uint64, uint32> renaming_;
	uint32 currentRenamingId_;

	void doRenaming(uint64& vertexId) {
		auto res = renaming_.emplace(vertexId, currentRenamingId_);
		vertexId = res.second ? currentRenamingId_++ : res.first->second;
	}

public:
	static const uint32 maxVertixNumber = UINT32_MAX;

	UndirectedGraph(const std::string& path) : currentRenamingId_(0) {
		std::ifstream inFile(path);
		if (!inFile.is_open()) {
			throw std::exception("File hasn't been opened.");
		}
		uint64 vertices;
		uint64 edges;
		char direction;

		inFile >> vertices >> edges >> direction;
		if (vertices > maxVertixNumber) {
			throw std::exception(std::string("The number of vertices is limited by " + std::to_string(maxVertixNumber)).c_str());
		}
		graph_.resize(vertices);

		std::vector<std::unordered_set<uint32>> uniqueList(vertices);
		uint64 fromId;
		uint64 toId;
		for (uint64 i = 0; i < edges; ++i) {
			inFile >> fromId >> toId;
			doRenaming(fromId);
			doRenaming(toId);
			if (uniqueList[fromId].emplace(toId).second) {
				uniqueList[toId].emplace(fromId);
				graph_[fromId].push_back(toId);
				graph_[toId].push_back(fromId);
			}
		}


		inFile.close();
	}

	uint32 vertixNumber() const {
		return graph_.size();
	}

	uint32 internalVertixName(uint64 v) const {
		auto it = renaming_.find(v);
		if (it == renaming_.end()) {
			return maxVertixNumber;
		}
		return it->second;
	}

	const std::vector<uint32>& internalAdj(uint32 v) const {
		return graph_[v];
	}

	uint64 internalDegree(uint32 v) const {
		return graph_[v].size();
	}
	
	uint32 findShortestPath(uint32 s, uint32 t, bool internalVertixRepresentationPassed = false) const {
		if (!internalVertixRepresentationPassed) {
			s = internalVertixName(s);
			t = internalVertixName(t);
			if (s == UndirectedGraph::maxVertixNumber || t == UndirectedGraph::maxVertixNumber) {
				throw std::exception("One of the vertices (s, t) doesn't exist.");
			}
		}
		else {
			if (s >= vertixNumber() || t >= vertixNumber()) {
				throw std::exception("One of the vertices (s, t) doesn't exist.");
			}
		}

		std::vector<uint32> dist(vertixNumber(), maxVertixNumber);
		dist[s] = 0;
		std::queue<uint32> q;
		q.push(s);
		uint32 v;
		while (!q.empty()) {
			v = q.front();
			q.pop();
			for (auto u : graph_[v]) {
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
};





#endif
