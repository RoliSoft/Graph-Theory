#ifndef EULER_PATH_H
#define EULER_PATH_H

#include <vector>
#include <boost/logic/tribool.hpp>
#include "graph.h"
#include "algo.h"
#include "edge.h"

class EulerPath : public GraphAlgo
{
public:
	std::vector<Edge*> path;

	EulerPath(Graph* graph);

	void search();
	void dump();

protected:
	virtual std::string name();
	virtual boost::tribool check(Vertex* vert, std::vector<Edge*>& visited);

private:
	bool recurse(Vertex* vert, std::vector<Edge*> visited);
};

#endif