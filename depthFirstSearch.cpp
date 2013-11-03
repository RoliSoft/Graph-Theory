#include <iostream>
#include <algorithm>
#include <boost/range/adaptor/map.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include "depthFirstSearch.h"

DepthFirstSearch::DepthFirstSearch(Graph* graph) : GraphSearch(graph)
{
	tock = std::map<Vertex*, int>();
	backEdges = std::vector<Edge*>();
}

void DepthFirstSearch::search()
{
	using namespace std;

	for (auto vert : graph->verts | boost::adaptors::map_values)
	{
		colors[vert] = color::white;
		tick[vert]   = 0;
		tock[vert]   = 0;
	}

	time = 0;
	acyclic = true;
	parentheses = "";

	for (auto vert : graph->verts | boost::adaptors::map_values)
	{
		if (colors[vert] == color::white)
		{
			discover(vert);

			grayed.emplace_back(nullptr);
			blacked.emplace_back(nullptr);
		}
	}

	cout << " Depth-first search:" << endl;
	printInfo();
	cout << endl;
}

void DepthFirstSearch::discover(Vertex* vert)
{
	colors[vert] = color::gray;
	tick[vert] = time;
	time++;
	grayed.emplace_back(vert);
	parentheses += "(";

	for (auto edge : vert->out)
	{
		switch (colors[edge->dst])
		{
		case color::white:
			categs[edge] = kind::tree;
			parents[edge->dst] = vert;
			discover(edge->dst);
			break;

		case color::gray:
			categs[edge] = kind::back;
			acyclic = false;
			backEdges.push_back(edge);
			break;

		case color::black:
			/*categs[edge] = std::distance(grayed.begin(), std::find(grayed.begin(), grayed.end(), vert)) < std::distance(grayed.begin(), std::find(grayed.begin(), grayed.end(), edge->dst))
						 ? kind::forward : kind::cross;*/
			categs[edge] = tick[vert] < tick[edge->dst] ? kind::forward : kind::cross;
			break;
		}
	}

	colors[vert] = color::black;
	tock[vert] = time;
	blacked.emplace_back(vert);
	parentheses += ")";
}

void DepthFirstSearch::discoverRev(Vertex* vert)
{
	colorsRev[vert] = color::gray;
	tickRev[vert] = timeRev;
	timeRev++;
	grayedRev.emplace_back(vert);

	for (auto edge : vert->in)
	{
		switch (colors[edge->src])
		{
		case color::white:
			categsRev[edge] = kind::tree;
			discover(edge->src);
			break;

		case color::gray:
			categsRev[edge] = kind::back;
			break;

		case color::black:
			categsRev[edge] = tickRev[vert] < tickRev[edge->src] ? kind::forward : kind::cross;
			break;
		}
	}

	colorsRev[vert] = color::black;
	tockRev[vert] = timeRev;
	blackedRev.emplace_back(vert);
}

void DepthFirstSearch::printInfo()
{
	GraphSearch::printInfo();

	using namespace std;

	cout << endl << "  Graph is " << (!acyclic ? "not " : "") << "acyclic." << endl;

	if (acyclic)
	{
		cout << endl << "  Topological sort:" << endl << "   ";

		bool first = true;
		for (auto vert : blacked | boost::adaptors::reversed | boost::adaptors::filtered([](void* x){return x != nullptr; }))
		{
			if (first)
			{
				first = false;
			}
			else
			{
				cout << ", ";
			}

			cout << vert->id;
		}

		cout << endl;
	}
	else
	{
		cout << endl << "  Cycles:" << endl << "   ";

		for (auto edge : backEdges)
		{
			cout << edge->src->id << " ";

			Vertex* parent = edge->src;
			while (parents.count(parent) > 0 && parent != edge->dst)
			{
				parent = parents[parent];
				cout << parent->id << " ";
			}

			cout << endl;
		}
	}
}