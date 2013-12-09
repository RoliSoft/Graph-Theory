#include <queue>
#include <boost/range/adaptor/map.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include "viterbiShortPath.h"
#include "depthFirstSearch.h"

ViterbiShortPath::ViterbiShortPath(Graph* graph, DepthFirstSearch* dfs)
	: GraphShortPath(graph),
	  dfs(dfs),
	  distance(std::unordered_map<Vertex*, int>()),
	  previous(std::unordered_map<Vertex*, Vertex*>())
{
}

void ViterbiShortPath::search(Vertex* source)
{
	using namespace std;

	if (source == nullptr)
	{
		source = (*graph->verts.begin()).second;
	}

	this->source = source;

	if (dfs == nullptr)
	{
		dfs = new DepthFirstSearch(graph);
	}

	if (dfs->blacked.size() == 0)
	{
		dfs->search();
	}

	for (auto vert : graph->verts | boost::adaptors::map_values)
	{
		distance[vert] = vert == source ? 0 : INT_MAX;
		previous[vert] = nullptr;
	}

	for (auto vert : dfs->blacked | boost::adaptors::reversed | boost::adaptors::filtered([](void* x){ return x != nullptr; }))
	{
		if (distance[vert] != INT_MAX)
		{
			for (auto edge : vert->out)
			{
				auto wert = edge->dst;

				if (distance[vert] + edge->weight < distance[wert])
				{
					distance[wert] = distance[vert] + edge->weight;
					previous[wert] = vert;
				}
			}
		}
	}
}

void ViterbiShortPath::dump()
{
	using namespace std;

	cout << " Viterbi's algorithm:" << endl << "  Shortest paths to " << source->id << ":" << endl << endl;

	for (auto vert : graph->verts | boost::adaptors::map_values)
	{
		cout << "   " << vert->id;

		if (distance[vert] == INT_MAX)
		{
			cout << ": not accessible.";
		}
		else
		{
			Vertex* wert = vert;
			int dist = distance[wert];
			while ((wert = previous[wert]) != nullptr)
			{
				cout << " -[" << (dist - distance[wert]) << "]-> " << wert->id;
				dist = distance[wert];
			}

			cout << " (" << distance[vert] << ")";
		}

		cout << endl;
	}

	cout << endl;
}