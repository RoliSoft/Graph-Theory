#include <iostream>
#include <boost/range/adaptor/map.hpp>
#include "breadthFirstSearch.h"

BreadthFirstSearch::BreadthFirstSearch(Graph* graph) : GraphSearch(graph)
{
}

void BreadthFirstSearch::search()
{
	using namespace std;

	auto queue = deque<Vertex*>();

	for (auto vert : graph->verts | boost::adaptors::map_values)
	{
		colors[vert] = color::white;
		tick[vert]   = 0;
	}

	parentheses = "";

	for (auto vert : graph->verts | boost::adaptors::map_values)
	{
		if (colors[vert] == color::white)
		{
			colors[vert] = color::gray;
			queue.push_back(vert);
			grayed.emplace_back(vert);
			parentheses += "(";

			while (!queue.empty())
			{
				auto svert = queue.front();
				queue.pop_front();

				for (auto edge : (graph->directed ? svert->out : svert->deg))
				{
					auto wert = (graph->directed ? edge->dst : (edge->dst == svert ? edge->src : edge->dst));

					switch (colors[wert])
					{
					case color::white:
						colors[wert] = color::gray;
						tick[wert] = tick[svert] + 1;
						categs[edge] = kind::tree;
						parents[wert] = svert;
						queue.push_back(wert);
						grayed.emplace_back(wert);
						parentheses += "(";
						break;

					case color::gray:
						categs[edge] = kind::back;
						break;

					case color::black:
						if (categs[edge] != kind::tree)
						{
							categs[edge] = tick[vert] <= tick[wert] + 1 ? kind::cross : kind::forward;
						}
						break;
					}
				}

				colors[svert] = color::black;
				blacked.emplace_back(svert);
				parentheses += ")";
			}

			grayed.emplace_back(nullptr);
			blacked.emplace_back(nullptr);
		}
	}
}

void BreadthFirstSearch::dump()
{
	using namespace std;

	cout << " Breadth-first search:" << endl;

	GraphSearch::dump();

	cout << endl << "  Shortest paths to first vertex via hop count:" << endl << endl;

	for (auto vert : graph->verts | boost::adaptors::map_values)
	{
		cout << "   " << vert->id;

		Vertex* parent = vert;
		while (parents.count(parent) > 0)
		{
			parent = parents[parent];
			cout << " -> " << parent->id;
		}

		cout << endl;
	}

	cout << endl;
}