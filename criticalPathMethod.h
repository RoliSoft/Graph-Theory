#ifndef CRITICAL_PATH_METHOD_H
#define CRITICAL_PATH_METHOD_H

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include "graph.h"
#include "algo.h"
#include "edge.h"

class CriticalPathMethod : public GraphAlgo
{
public:
	int length;
	std::vector<Vertex*> path;

	CriticalPathMethod(Graph* graph);

	void search();
	void dump();

private:
	int getMaxForward(Vertex* vert);
	int getMaxBackward(Vertex* vert);
};

#endif