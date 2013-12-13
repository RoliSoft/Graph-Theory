#ifndef FORD_FULKERSON_MAX_FLOW_H
#define FORD_FULKERSON_MAX_FLOW_H

#include <map>
#include <boost/numeric/ublas/matrix.hpp>
#include "graph.h"
#include "algo.h"
#include "edge.h"

class FordFulkersonMaxFlow : public GraphAlgo
{
public:
	int maxFlow;
	boost::numeric::ublas::matrix<int> capacity, flow;
	std::map<Vertex*, Vertex*> parent;

	FordFulkersonMaxFlow(Graph* graph);

	void search();
	void dump();

private:
	bool breadthFirstSearch();
};

#endif