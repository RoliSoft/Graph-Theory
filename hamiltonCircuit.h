#ifndef HAMILTON_CIRCUIT_H
#define HAMILTON_CIRCUIT_H

#include <vector>
#include <boost/logic/tribool.hpp>
#include "graph.h"
#include "algo.h"
#include "edge.h"
#include "hamiltonPath.h"

class HamiltonCircuit : public HamiltonPath
{
public:
	HamiltonCircuit(Graph* graph);

protected:
	virtual std::string name();
	virtual boost::tribool check(Vertex* vert, std::vector<Vertex*>& visited);
};

#endif