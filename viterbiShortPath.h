#ifndef VITERBI_SHORT_PATH_H
#define VITERBI_SHORT_PATH_H

#include <unordered_map>
#include "graph.h"
#include "shortPath.h"
#include "edge.h"

class DepthFirstSearch;

class ViterbiShortPath : public GraphShortPath
{
public:
	std::unordered_map<Vertex*, int> distance;
	std::unordered_map<Vertex*, Vertex*> previous;
	Vertex* source;
	DepthFirstSearch* dfs;

	ViterbiShortPath(Graph* graph, DepthFirstSearch* dfs = nullptr);

	void search(Vertex* source = nullptr);
	void dump();
};

#endif