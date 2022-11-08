#pragma once

#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
#include<algorithm>

/*
* Unweighted GRAPH
*/
struct GraphNode {
	std::vector<GraphNode*> mAdjacents;
};
struct Graph {
	std::vector<GraphNode*> mNodes;
};
/*
* Weighted GRAPH
*/
struct WeightedEdge {
	struct WeightedGraphNode* mFromNode;
	struct WeightedGraphNode* mToNode;
	float weight;
};
struct WeightedGraphNode {
	std::vector<WeightedEdge*> mEdges;
	float x, y;
};
struct WeightedGraph {
	std::vector<WeightedGraphNode*> mNodes;
};
// Greedy Breadth-first-search
struct GBFSScratch {
	const WeightedEdge* mParentEdge = nullptr;
	float mHeuristic = 0.0f;
	bool mInClosedSet = false;
	bool mInOpenSet = false;
};

using NodeToParentMap = std::unordered_map<const GraphNode*, const GraphNode*>;
using GBFSMap = std::unordered_map<const WeightedGraphNode*, GBFSScratch>;

// Compute Mahattan Heuristic
float ComputeMahattanHeuristic(const WeightedGraphNode* firstNode, const WeightedGraphNode* secondNode) {
	return std::abs(firstNode->x - secondNode->x) + std::abs(firstNode->y - secondNode->y);
}
// Compute Euclidean Heuristic
float ComputeEuclideanHeuristic(const WeightedGraphNode* firstNode, const WeightedGraphNode* secondNode) {
	return std::sqrtf(std::pow(firstNode->x - secondNode->x, 2) + std::pow(firstNode->y - secondNode->y, 2));
}

class GraphAlgorithm {
public:
	// Breadth-first-search
	static bool BFS(const Graph& graph, const GraphNode* start, const GraphNode* end, NodeToParentMap& outMap)
	{
		bool pathFound = false;
		std::queue<const GraphNode*> traverseNodes;
		traverseNodes.emplace(start);

		while (!traverseNodes.empty()) {
			const GraphNode* currentNode = traverseNodes.front();
			traverseNodes.pop();

			if (currentNode == end) {
				pathFound = true;
				break;
			}

			// Insert current node adjacent into the queue
			for (const GraphNode* adjacent : currentNode->mAdjacents) {
				const GraphNode* parent = outMap[adjacent];
				if (parent == nullptr && adjacent != start) {
					outMap[adjacent] = currentNode;
					traverseNodes.emplace(adjacent);
				}
			}
		}

		return pathFound;
	}

	static bool GBFS(const WeightedGraph& graph, const WeightedGraphNode* start,
		const WeightedGraphNode* goal, GBFSMap& outMap)
	{
		std::vector<const WeightedGraphNode*> openSet;
		const WeightedGraphNode* currentNode = start;
		outMap[currentNode].mInClosedSet = true;

		do {
			// Add node adjacent to open set
			for (const WeightedEdge* edge : currentNode->mEdges) {
				GBFSScratch& data = outMap[edge->mToNode];
				if (!data.mInClosedSet) {
					data.mParentEdge = edge;

					if (!data.mInOpenSet) {
						data.mHeuristic = ComputeMahattanHeuristic(edge->mToNode, goal);
						data.mInOpenSet = true;

						openSet.emplace_back(edge->mToNode);
					}
				}
			}

			if (openSet.empty()) {
				break;
			}

			// Find node with lowest Heurisitc Cost
			auto iter = std::min_element(openSet.begin(), openSet.end(),
				[&outMap](const WeightedGraphNode* firstNode, const WeightedGraphNode* secondNode) {
				return outMap[firstNode].mHeuristic < outMap[secondNode].mHeuristic;
			});

			currentNode = (*iter);
			openSet.erase(iter);
			outMap[currentNode].mInOpenSet = false;
			outMap[currentNode].mInClosedSet = true;

		} while (currentNode != goal);

		return currentNode == goal;
	}


	static std::queue<const GraphNode*>& GetPath(const Graph& graph, const GraphNode* start,
		const GraphNode* end, NodeToParentMap& map)
	{
		bool foundPath = GraphAlgorithm::BFS(graph, end, start, map);
		std::queue<const GraphNode*> path;

		if (foundPath) {
			const GraphNode* currentNode = map[start];
			while (currentNode != nullptr) {
				path.emplace(currentNode);
				currentNode = map[currentNode];
			}
		}

		return path;
	}

	static std::queue<const WeightedGraphNode*>& GetPath(const WeightedGraph& graph, const WeightedGraphNode* start,
		const WeightedGraphNode* end, GBFSMap& map)
	{
		bool foundPath = GraphAlgorithm::GBFS(graph, end, start, map);
		std::queue<const WeightedGraphNode*> path = std::queue<const WeightedGraphNode*>();

		// TODO: extract node from edges
		if (foundPath) {

		}

		return path;
	}
};