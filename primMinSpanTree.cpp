#include <unordered_set>
#include "primMinSpanTree.h"

PrimMinSpanTree::PrimMinSpanTree(Graph* graph)
	: GraphAlgo(graph),
	  tree(std::vector<Edge*>()),
	  weight(0)
{
}

void PrimMinSpanTree::search()
{
	using namespace std;

	unordered_set<Vertex*> verts;
	unordered_set<Edge*> edges;
	
	verts.emplace((*graph->verts.begin()).second);

	while (edges.size() != graph->verts.size() - 1)
	{
		bool bdir = false;
		Edge* best = nullptr;

		for (auto vert : verts)
		{
			for (auto edge : vert->deg)
			{
				Vertex* wert;
				bool dir;

				if (edge->dst == vert)
				{
					wert = edge->src;
					dir  = false;
				}
				else
				{
					wert = edge->dst;
					dir  = true;
				}

				if ((best == nullptr || best->weight >= edge->weight)
				 && (verts.find(wert) == verts.end() && edges.find(edge) == edges.end()))
				{
					best = edge;
					bdir = dir;
				}
			}
		}

		if (best == nullptr)
		{
			break;
		}

		verts.emplace(bdir ? best->dst : best->src);
		edges.emplace(best);
		tree.push_back(best);

		weight += best->weight;
	}

	printInfo();
}


void PrimMinSpanTree::printInfo()
{
	using namespace std;

	cout << " Prim's algorithm:" << endl << "  Minimum spanning tree:" << endl << endl;

	for (auto edge : tree)
	{
		cout << "   " << edge->src->id << " <-[" << edge->weight << "]-> " << edge->dst->id << endl;
	}

	cout << endl << "  Total path weight: " << weight << endl << endl;
}