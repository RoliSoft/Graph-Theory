#include <boost/range/adaptor/map.hpp>
#include "hamiltonPath.h"

HamiltonPath::HamiltonPath(Graph* graph)
	: GraphAlgo(graph),
	  path(std::vector<Vertex*>())
{
}

void HamiltonPath::search()
{
	std::vector<Vertex*> visited;

	for (auto vert : graph->verts | boost::adaptors::map_values)
	{
		visited.push_back(vert);

		if (recurse(vert, visited))
		{
			break;
		}

		visited.clear();
	}
}

void HamiltonPath::dump()
{
	using namespace std;

	cout << " Hamilton's path:" << endl << "  ";

	if (path.size() == 0)
	{
		cout << "No Hamiltonian path available for the graph." << endl << endl;
		return;
	}

	bool first = true;

	for (auto vert : path)
	{
		if (first)
		{
			first = false;
		}
		else
		{
			cout << " -> ";
		}

		cout << vert->id;
	}

	cout << endl << endl;
}

bool HamiltonPath::recurse(Vertex* vert, std::vector<Vertex*> visited)
{
	if (visited.size() == graph->verts.size())
	{
		path = visited;
		return true;

		/*for (auto edge : vert->deg)
		{
			if ((edge->dst == vert ? edge->src : edge->dst) == visited[0])
			{
				path = visited;
				return true;
			}
		}

		return false;*/
	}

	for (auto edge : vert->deg)
	{
		std::vector<Vertex*> visitcpy(visited);

		auto wert = edge->dst == vert ? edge->src : edge->dst;

		if (std::find(visitcpy.begin(), visitcpy.end(), wert) != visitcpy.end())
		{
			continue;
		}

		visitcpy.push_back(wert);

		if (recurse(wert, visitcpy))
		{
			return true;
		}
	}

	return false;
}