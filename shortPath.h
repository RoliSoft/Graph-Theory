#ifndef SHORT_PATH_H
#define SHORT_PATH_H

#include "graph.h"
#include "algo.h"
#include "vertex.h"
#include "algo.h"

class GraphShortPath : public GraphAlgo
{
public:
	GraphShortPath(Graph* graph);

	virtual void search(Vertex* source = nullptr) = 0;
	virtual void dump() = 0;
};

#endif