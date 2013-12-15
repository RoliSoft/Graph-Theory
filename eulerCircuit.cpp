#include "eulerCircuit.h"

EulerCircuit::EulerCircuit(Graph* graph)
	: EulerPath(graph)
{
}

std::string EulerCircuit::name()
{
	return "circuit";
}

boost::tribool EulerCircuit::check(Vertex* vert, std::vector<Edge*>& visited)
{
	if (visited.size() == graph->edges.size())
	{
		for (auto edge : vert->deg)
		{
			if (edge == visited[0])
			{
				return true;
			}
		}

		return false;
	}

	return boost::indeterminate;
}