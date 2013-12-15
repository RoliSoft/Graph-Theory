#ifndef HAMILTON_PATH_H
#define HAMILTON_PATH_H

#include <vector>
#include <boost/logic/tribool.hpp>
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
	virtual std::string name();
	virtual boost::tribool check(Vertex* vert, std::vector<Vertex*>& visited);

private:
	bool recurse(Vertex* vert, std::vector<Vertex*> visited);
};

#endif