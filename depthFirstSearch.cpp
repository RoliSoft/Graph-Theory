#include <iostream>
#include <algorithm>
#include <boost/range/adaptor/map.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include "depthFirstSearch.h"

DepthFirstSearch::DepthFirstSearch(Graph* graph) : GraphSearch(graph)
{
	tock       = std::map<Vertex*, int>();
	bmin       = std::map<Vertex*, int>();
	backEdges  = std::vector<Edge*>();
	artEdges   = std::unordered_set<Edge*>();
	artVerts   = std::unordered_set<Vertex*>();
	colorsRev  = std::map<Vertex*, color>();
	grayedRev  = std::vector<Vertex*>();
	blackedRev = std::vector<Vertex*>();
	categsRev  = std::map<Edge*, kind>();
	tickRev    = std::map<Vertex*, int>();
	tockRev    = std::map<Vertex*, int>();
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

void DepthFirstSearch::searchRev()
{
	using namespace std;

	for (auto vert : graph->verts | boost::adaptors::map_values)
	{
		colorsRev[vert] = color::white;
		tickRev[vert]   = 0;
		tockRev[vert]   = 0;
	}

	timeRev = 0;

	for (auto vert : blacked | boost::adaptors::reversed)
	{
		if (colorsRev[vert] == color::white)
		{
			discoverRev(vert);

			grayedRev.emplace_back(nullptr);
			blackedRev.emplace_back(nullptr);
		}
	}

	cout << " Reverse depth-first search:" << endl;
	printInfoRev();
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

			if (bmin[edge->dst] > tick[vert])
			{
				artEdges.emplace(edge);
			}

			if ((parents.count(vert) == 0 && vert->out.size() > 1)
			 || (parents.count(vert) != 0 && bmin[edge->dst] >= tick[vert]))
			{
				artVerts.emplace(vert);
			}
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

void DepthFirstSearch::discoverRev(Vertex* vert)
{
	colorsRev[vert] = color::gray;
	tickRev[vert] = timeRev;
	timeRev++;
	grayedRev.emplace_back(vert);

	for (auto edge : vert->in)
	{
		switch (colorsRev[edge->src])
		{
		case color::white:
			categsRev[edge] = kind::tree;
			discoverRev(edge->src);
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

void DepthFirstSearch::printInfoRev()
{
	using namespace std;

	cout << "  Strongly connected components:  " << endl << "   ";

	auto sep = false;
	for (auto vert : grayedRev)
	{
		if (vert == nullptr)
		{
			sep = true;
		}
		else
		{
			if (sep)
			{
				cout << endl << "   ";
				sep = false;
			}

			cout << vert->id << " ";
		}
	}

	cout << endl;
}