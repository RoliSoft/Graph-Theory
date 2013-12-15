#include "hamiltonCircuit.h"

HamiltonCircuit::HamiltonCircuit(Graph* graph)
	: HamiltonPath(graph)
{
}

std::string HamiltonCircuit::name()
{
	return "circuit";
}

boost::tribool HamiltonCircuit::check(Vertex* vert, std::vector<Vertex*> visited)
{
	if (visited.size() == graph->verts.size())
	{
		for (auto edge : vert->deg)
		{
			if ((edge->dst == vert ? edge->src : edge->dst) == visited[0])
			{
				return true;
			}
		}

		return false;
	}

	return boost::indeterminate;
}