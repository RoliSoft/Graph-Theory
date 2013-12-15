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

	cout << " Hamilton's " << name() << ":" << endl << "  ";

	if (path.size() == 0)
	{
		cout << "No Hamiltonian " << name() << " available for the graph." << endl << endl;
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

std::string HamiltonPath::name()
{
	return "path";
}

boost::tribool HamiltonPath::check(Vertex* vert, std::vector<Vertex*>& visited)
{
	if (visited.size() == graph->verts.size())
	{
		return true;
	}

	return boost::indeterminate;
}

bool HamiltonPath::recurse(Vertex* vert, std::vector<Vertex*> visited)
{
	boost::tribool cres;
	if (!boost::indeterminate(cres = check(vert, visited)))
	{
		if (cres)
		{
			path = visited;
		}

		return cres;
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