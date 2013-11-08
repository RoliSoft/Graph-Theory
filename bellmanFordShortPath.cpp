#include <queue>
#include <boost/range/adaptor/map.hpp>
#include "bellmanFordShortPath.h"

BellmanFordShortPath::BellmanFordShortPath(Graph* graph)
	: GraphAlgo(graph),
	  distance(std::unordered_map<Vertex*, int>()),
	  previous(std::unordered_map<Vertex*, Vertex*>())
{
}

void BellmanFordShortPath::search(Vertex* source)
{
	using namespace std;

	if (source == nullptr)
	{
		source = (*graph->verts.begin()).second;
	}

	this->source = source;

	for (auto vert : graph->verts | boost::adaptors::map_values)
	{
		distance[vert] = vert == source ? 0 : INT_MAX;
		previous[vert] = nullptr;
	}
	
	for (int i = 0; i < (int)graph->verts.size(); i++)
	{
		for (auto vert : graph->verts | boost::adaptors::map_values)
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

	negCycle = false;

	for (auto vert : graph->verts | boost::adaptors::map_values)
	{
		for (auto edge : vert->out)
		{
			auto wert = edge->dst;

			if (distance[vert] + edge->weight < distance[wert])
			{
				negCycle = true;
				break;
			}
		}

		if (negCycle)
		{
			break;
		}
	}

	printInfo();
}


void BellmanFordShortPath::printInfo()
{
	using namespace std;

	cout << " Bellman-Ford's algorithm:" << endl << "  Shortest paths to " << source->id << ":" << endl << endl;

	if (negCycle)
	{
		cout << "   Graph contains a negative-weight cycle!" << endl << endl;
	}

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