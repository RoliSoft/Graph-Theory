#include <unordered_map>
#include "kruskalMinSpanTree.h"

KruskalMinSpanTree::KruskalMinSpanTree(Graph* graph)
	: GraphAlgo(graph),
	  tree(std::vector<Edge*>()),
	  weight(0)
{
}

void KruskalMinSpanTree::search()
{
	using namespace std;

	unordered_map<int, int> prep;

	for (auto vert : graph->verts)
	{
		prep[vert.first] = vert.first;
	}

	vector<Edge*> edgeAsc(graph->edges.begin(), graph->edges.end());

	sort(edgeAsc.begin(), edgeAsc.end(), [](const Edge* a, const Edge* b){ return a->weight < b->weight; });
	
	for (auto edge : edgeAsc)
	{
		auto src = prep[edge->src->id];
		auto dst = prep[edge->dst->id];

		if (src != dst)
		{
			tree.push_back(edge);

			for (auto& vert : prep)
			{
				if (vert.second == dst)
				{
					vert.second = src;
				}
			}

			weight += edge->weight;
		}
	}
}

void KruskalMinSpanTree::dump()
{
	using namespace std;

	cout << " Kruskal's algorithm:" << endl << "  Minimum spanning tree:" << endl << endl;

	for (auto edge : tree)
	{
		cout << "   " << edge->src->id << " <-[" << edge->weight << "]-> " << edge->dst->id << endl;
	}

	cout << endl << "  Total path weight: " << weight << endl << endl;
}