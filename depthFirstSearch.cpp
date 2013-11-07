#include <iostream>
#include <algorithm>
#include <boost/range/adaptor/map.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include "depthFirstSearch.h"

DepthFirstSearch::DepthFirstSearch(Graph* graph)
	: GraphSearch(graph),
	  tock(std::map<Vertex*, int>()),
	  levels(std::map<Vertex*, int>()),
	  backEdges(std::unordered_set<Edge*>()),
	  artEdges(std::unordered_set<Edge*>()),
	  artVerts(std::unordered_set<Vertex*>())
{
}

void DepthFirstSearch::search()
{
	using namespace std;

	for (auto vert : graph->verts | boost::adaptors::map_values)
	{
		colors[vert] = color::white;
		tick[vert] = tock[vert] = levels[vert] = 0;
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

int DepthFirstSearch::discover(Vertex* vert, int level)
{
	colors[vert] = color::gray;
	tick[vert] = time++;
	levels[vert] = level;
	grayed.emplace_back(vert);
	parentheses += "(";
	int uminvm, rfminvm = INT_MAX, child = 0, cutchild = 0;

	for (auto edge : (graph->directed ? vert->out : vert->deg))
	{
		auto wert = (graph->directed ? edge->dst : (edge->dst == vert ? edge->src : edge->dst));

		switch (colors[wert])
		{
		case color::white:
			categs[edge] = kind::tree;
			parents[wert] = vert;
			child++;

			uminvm = discover(wert, level + 1);

			if (uminvm < level)
			{
				if (uminvm < rfminvm)
				{
					rfminvm = uminvm;
				}
			}
			else
			{
				cutchild++;
			}
			break;

		case color::gray:
			categs[edge] = kind::back;
			acyclic = false;

			backEdges.emplace(edge);

			if (levels[wert] < level - 1 && levels[wert] < rfminvm)
			{
				rfminvm = levels[wert];
			}
			break;

		case color::black:
			categs[edge] = tick[vert] < tick[wert] ? kind::forward : kind::cross;
			break;
		}
	}

	colors[vert] = color::black;
	tock[vert] = time;
	blacked.emplace_back(vert);
	parentheses += ")";

	if (parents.count(vert) != 0)
	{
		if (cutchild > 0)
		{
			artVerts.emplace(vert);
		}

		if (rfminvm == INT_MAX)
		{
			artEdges.emplace(new Edge(parents[vert], vert));
		}
	}
	else
	{
		if (child > 1)
		{
			artVerts.emplace(vert);
		}
	}

	return rfminvm;
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
		if (graph->directed)
		{
			cout << endl << "  Cycles:" << endl;

			for (auto edge : backEdges)
			{
				cout << "   " << edge->src->id;

				Vertex* parent = edge->src;
				while (parents.count(parent) > 0 && parent != edge->dst)
				{
					parent = parents[parent];
					cout << " -> " << parent->id;
				}

				cout << endl;
			}
		}
	}

	cout << endl << "  Articulation edges:" << endl;

	for (auto edge : artEdges)
	{
		cout << "   " << edge->src->id << " -> " << edge->dst->id << endl;
	}

	cout << endl << "  Articulation vertices:" << endl << "   ";

	bool frst = true;
	for (auto vert : artVerts)
	{
		if (frst)
		{
			frst = false;
		}
		else
		{
			cout << ", ";
		}

		cout << vert->id;
	}

	cout << endl;
}