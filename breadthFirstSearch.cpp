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

				for (auto edge : svert->out)
				{
					switch (colors[edge->dst])
					{
					case color::white:
						colors[edge->dst] = color::gray;
						tick[edge->dst] = tick[svert] + 1;
						categs[edge] = kind::tree;
						parents[edge->dst] = svert;
						queue.push_back(edge->dst);
						grayed.emplace_back(edge->dst);
						parentheses += "(";
						break;

					case color::gray:
						categs[edge] = kind::back;
						break;

					case color::black:
						if (categs[edge] != kind::tree)
						{
							categs[edge] = tick[vert] <= tick[edge->dst] + 1 ? kind::cross : kind::forward;
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

	cout << " Breadth-first search:" << endl;
	printInfo();
	cout << endl;
}