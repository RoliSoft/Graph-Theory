#include <queue>
#include <boost/range/adaptor/map.hpp>
#include "dijkstraShortPath.h"

DijkstraShortPath::DijkstraShortPath(Graph* graph)
	: GraphAlgo(graph),
	  distance(std::unordered_map<Vertex*, int>()),
	  previous(std::unordered_map<Vertex*, Vertex*>())
{
}

void DijkstraShortPath::search(Vertex* source)
{
	using namespace std;

	if (source == nullptr)
	{
		source = (*graph->verts.begin()).second;
	}

	this->source = source;

	queue<pair<int, Vertex*>> vueue;

	for (auto vert : graph->verts | boost::adaptors::map_values)
	{
		distance[vert] = INT_MAX;
		previous[vert] = nullptr;
	}

	distance[source] = 0;

	vueue.push(make_pair(distance[source], source));

	while (!vueue.empty())
	{
		auto vert = vueue.front();
		vueue.pop();

		for (auto edge : vert.second->out)
		{
			auto wert = edge->dst;
			auto dist = vert.first + edge->weight;

			if (dist < distance[wert])
			{
				distance[wert] = dist;
				previous[wert] = vert.second;

				vueue.push(make_pair(dist, wert));
			}
		}
	}

	printInfo();
}


void DijkstraShortPath::printInfo()
{
	using namespace std;

	cout << " Dijkstra's algorithm:" << endl << "  Shortest paths to " << source->id << ":" << endl << endl;

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