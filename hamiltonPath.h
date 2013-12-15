#ifndef HAMILTON_PATH_H
#define HAMILTON_PATH_H

#include <unordered_set>
#include <vector>
#include "graph.h"
#include "algo.h"
#include "edge.h"

class HamiltonPath : public GraphAlgo
{
public:
	std::vector<Vertex*> path;

	HamiltonPath(Graph* graph);

	void search();
	void dump();

protected:
	bool circuit;

private:
	bool recurse(Vertex* vert, std::vector<Vertex*> visited);
};

#endif