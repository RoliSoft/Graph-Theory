#include <boost/range/adaptor/map.hpp>
#include "eulerPath.h"

EulerPath::EulerPath(Graph* graph)
	: GraphAlgo(graph),
	  path(std::vector<Edge*>())
{
}

void EulerPath::search()
{
	std::vector<Edge*> visited;

	for (auto vert : graph->verts | boost::adaptors::map_values)
	{
		//visited.push_back(vert);

		if (recurse(vert, visited))
		{
			break;
		}

		visited.clear();
	}
}

void EulerPath::dump()
{
	using namespace std;

	cout << " Euler's " << name() << ":" << endl;

	if (path.size() == 0)
	{
		cout << "  No Eulerian " << name() << " available for the graph." << endl << endl;
		return;
	}

	Vertex* last = nullptr;

	for (auto edge : path)
	{
		bool swap = last == edge->dst;
		last = edge->dst;

		cout << "  " << (swap ? edge->dst : edge->src)->id << " <-> " << (swap ? edge->src : edge->dst)->id << endl;
	}

	cout << endl;
}

std::string EulerPath::name()
{
	return "path";
}

boost::tribool EulerPath::check(Vertex* vert, std::vector<Edge*>& visited)
{
	if (visited.size() == graph->edges.size())
	{
		return true;
	}

	return boost::indeterminate;
}

bool EulerPath::recurse(Vertex* vert, std::vector<Edge*> visited)
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
		std::vector<Edge*> visitcpy(visited);

		auto wert = edge->dst == vert ? edge->src : edge->dst;

		if (std::find(visitcpy.begin(), visitcpy.end(), edge) != visitcpy.end())
		{
			continue;
		}

		visitcpy.push_back(edge);

		if (recurse(wert, visitcpy))
		{
			return true;
		}
	}

	return false;
}