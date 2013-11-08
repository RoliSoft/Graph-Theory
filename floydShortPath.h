#ifndef FLOYD_SHORT_PATH_H
#define FLOYD_SHORT_PATH_H

#include <boost/numeric/ublas/matrix.hpp>
#include "graph.h"
#include "algo.h"
#include "edge.h"

class FloydShortPath : public GraphAlgo
{
public:
	boost::numeric::ublas::matrix<int> paths;

	FloydShortPath(Graph* graph);

	void search();
	void dump();
};

#endif