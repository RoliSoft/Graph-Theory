#include <iostream>
#include "search.h"

GraphSearch::GraphSearch(Graph* graph)
	: GraphAlgo(graph),
	  colors(std::map<Vertex*, color>()),
	  grayed(std::vector<Vertex*>()),
	  blacked(std::vector<Vertex*>()),
	  categs(std::map<Edge*, kind>()),
	  parents(std::map<Vertex*, Vertex*>()),
	  tick(std::map<Vertex*, int>())
{
}

void GraphSearch::printInfo()
{
	using namespace std;

	cout << "  Gray:  ";

	auto sep = false;
	for (auto vert : grayed)
	{
		if (vert == nullptr)
		{
			sep = true;
		}
		else
		{
			if (sep)
			{
				cout << "| ";
				sep = false;
			}
			
			cout << vert->id << " ";
		}
	}

	cout << endl << "  Black: ";

	sep = false;
	for (auto vert : blacked)
	{
		if (vert == nullptr)
		{
			sep = true;
		}
		else
		{
			if (sep)
			{
				cout << "| ";
				sep = false;
			}
			
			cout << vert->id << " ";
		}
	}

	cout << endl << "  Progress: " << parentheses << endl << endl;

	map<kind, string> classes = {
		{ kind::_undefk, "undetermined" },
		{ kind::tree, "tree" },
		{ kind::back, "back" },
		{ kind::cross, "cross" },
		{ kind::forward, "forward" },
	};

	for (auto edge : graph->edges)
	{
		cout << "  " << edge->src->id << " -> " << edge->dst->id << " is a " << classes[categs[edge]] << " edge." << endl;
	}

	cout << endl;

	for (auto vert : parents)
	{
		cout << "  Parent of vertex " << vert.first->id << " is " << vert.second->id << "." << endl;
	}
}