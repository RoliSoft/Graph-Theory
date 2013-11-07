#include <iostream>
#include <algorithm>
#include <boost/range/adaptor/map.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include "depthFirstSearch.h"

DepthFirstSearch::DepthFirstSearch(Graph* graph)
	: GraphSearch(graph),
	  tock(std::map<Vertex*, int>()),
	  bmin(std::map<Vertex*, int>()),
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
		bmin[vert]   = 0;
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

	for (auto vert : graph->verts | boost::adaptors::map_values)
	{
		for (auto edge : vert->out)
		{
			if (bmin[edge->dst] > tick[vert])
			{
				artEdges.emplace(edge);
			}

			if ((parents.count(vert) == 0 && vert->out.size() > 1)
			 || (parents.count(vert) != 0 && bmin[edge->dst] >= tick[vert]))
			{
				artVerts.emplace(vert);
			}
		}
	}

	cout << " Depth-first search:" << endl;
	printInfo();
	cout << endl;
}

void DepthFirstSearch::discover(Vertex* vert)
{
	colors[vert] = color::gray;
	tick[vert] = bmin[vert] = time;
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

			bmin[vert] = std::min(bmin[vert], bmin[edge->dst]);
			break;

		case color::gray:
			categs[edge] = kind::back;
			acyclic = false;

			backEdges.push_back(edge);

			if (edge->dst != parents[vert])
			{
				bmin[vert] = std::min(bmin[vert], tick[edge->dst]);
			}
			break;

		case color::black:
			categs[edge] = tick[vert] < tick[edge->dst] ? kind::forward : kind::cross;

			if (edge->dst != parents[vert])
			{
				bmin[vert] = std::min(bmin[vert], tick[edge->dst]);
			}
			break;
		}
	}

	colors[vert] = color::black;
	tock[vert] = time;
	blacked.emplace_back(vert);
	parentheses += ")";
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