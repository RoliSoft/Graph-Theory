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
	boost::numeric::ublas::matrix<Vertex*> nexts;

	FloydShortPath(Graph* graph);

	void search();
	void path(Vertex* src, Vertex* dst);
	void dump();

private:
	std::string _path(Vertex* src, Vertex* dst, int& sum);
};

#endif