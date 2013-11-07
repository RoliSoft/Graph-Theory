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
	  backEdges(std::vector<Edge*>()),
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
		tick[vert]   = 0;
		tock[vert]   = 0;
		levels[vert] = 0;
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
	int uminvm, rfminvm = INT_MAX;

	for (auto edge : vert->out)
	{
		switch (colors[edge->dst])
		{
		case color::white:
			categs[edge] = kind::tree;
			parents[edge->dst] = vert;

			uminvm = discover(edge->dst, level + 1);

			if (uminvm < level && uminvm < rfminvm)
			{
				rfminvm = uminvm;
			}
			break;

		case color::gray:
			categs[edge] = kind::back;
			acyclic = false;

			backEdges.push_back(edge);

			if (levels[edge->dst] < level - 1 && levels[edge->dst] < rfminvm)
			{
				rfminvm = levels[edge->dst];
			}
			break;

		case color::black:
			categs[edge] = tick[vert] < tick[edge->dst] ? kind::forward : kind::cross;
			break;
		}
	}

	colors[vert] = color::black;
	tock[vert] = time;
	blacked.emplace_back(vert);
	parentheses += ")";

	if (parents.count(vert) != 0 && rfminvm == INT_MAX)
	{
		artEdges.emplace(new Edge(parents[vert], vert));
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
		cout << endl << "  Cycles:" << endl;

		for (auto edge : backEdges)
		{
			cout << "   " << edge->src->id << " ";

			Vertex* parent = edge->src;
			while (parents.count(parent) > 0 && parent != edge->dst)
			{
				parent = parents[parent];
				cout << parent->id << " ";
			}

			cout << endl;
		}
	}

	cout << endl << "  Articulation edges:" << endl;

	for (auto edge : artEdges)
	{
		cout << "   " << edge->src->id << " " << edge->dst->id << endl;
	}

	cout << endl << "  Articulation vertices:" << endl << "   ";

	for (auto vert : artVerts)
	{
		cout << vert->id << " ";
	}

	cout << endl;
}