#include <iostream>
#include <fstream>
#include <iomanip>
#include <deque>
#include <boost/range/adaptor/map.hpp>
#include "graph.h"

Graph::Graph(std::string file)
{
	using namespace std;

	cout << "Initializing graph from file..." << endl << endl;

	ifstream fs(file);

	fs >> directed;
	fs >> weighted;
	fs >> vertCnt;
	fs >> edgeCnt;

	cout << " Number of vertices: " << vertCnt << "; edges: " << edgeCnt << "; graph is " << (!directed ? "not " : "") << "directed and " << (!weighted ? "not " : "") << "weighted." << endl << endl;

	verts  = map<int, Vertex*>();
	edges  = vector<Edge*>(edgeCnt);
	matrix = Matrix<bool>(vertCnt + 1, vertCnt + 1, false);

	if (weighted)
	{
		weightrix = Matrix<int>(vertCnt + 1, vertCnt + 1, INT_MAX);
	}
	
	for (int i = 0; i < edgeCnt; i++)
	{
		int src, dst, weight = 0;

		fs >> src;
		fs >> dst;

		if (weighted)
		{
			fs >> weight;
		}

		if (!verts.count(src))
		{
			verts.emplace(src, new Vertex(this, src));
		}

		if (!verts.count(dst))
		{
			verts.emplace(dst, new Vertex(this, dst));
		}

		edges[i] = new Edge(verts[src], verts[dst], weight);

		matrix.set(edges[i]->src->id, edges[i]->dst->id, true);

		if (!directed)
		{
			matrix.set(edges[i]->dst->id, edges[i]->src->id, true);
		}

		if (weighted)
		{
			weightrix.set(edges[i]->src->id, edges[i]->dst->id, weight);

			if (!directed)
			{
				weightrix.set(edges[i]->dst->id, edges[i]->src->id, weight);
			}
		}

		cout << "  " << edges[i]->src->id << " " << (!directed ? "<" : "") << "-" << (weighted ? "[" + to_string(edges[i]->weight) + "]" : "") << "-> " << edges[i]->dst->id << endl;
	}

	cout << endl << " Edge list:" << endl;

	for (auto vert : verts | boost::adaptors::map_values)
	{
		cout << endl << "  Vertex " << vert->id << ": " << endl;

		if (directed)
		{
			cout << "   <-  in: " << vert->in.size() << " [ ";

			for (auto ed : vert->in)
			{
				cout << ed->src->id << " ";
			}

			cout << "]" << endl << "   -> out: " << vert->out.size() << " [ ";

			for (auto ed : vert->out)
			{
				cout << ed->dst->id << " ";
			}

			cout << "]" << endl;
		}
		else
		{
			cout << "   degree: " << vert->deg.size() << " [ ";

			for (auto ed : vert->deg)
			{
				cout << (ed->dst == vert ? ed->src->id : ed->dst->id) << " ";
			}

			cout << "]" << endl;
		}
	}

	cout << endl << " Adjacency matrix:" << endl;
	matrix.print();

	if (weighted)
	{
		cout << " Weighted adjacency matrix:" << endl;
		weightrix.print();
	}
}