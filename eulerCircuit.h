#ifndef EULER_CIRCUIT_H
#define EULER_CIRCUIT_H

#include <vector>
#include <boost/logic/tribool.hpp>
#include "graph.h"
#include "algo.h"
#include "edge.h"
#include "eulerPath.h"

class EulerCircuit : public EulerPath
{
public:
	EulerCircuit(Graph* graph);

protected:
	virtual std::string name();
	virtual boost::tribool check(Vertex* vert, std::vector<Edge*>& visited);
};

#endif