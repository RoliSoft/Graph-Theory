#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <deque>
#include <vector>
#include <tuple>
#include <type_traits>
#include <set>
#include <boost/optional.hpp>
#include <boost/range/adaptor/map.hpp>
#include "graph.h"

Graph::Graph(std::string file)
{
	using namespace std;

	cout << "Reading graph from file..." << endl;

	string line;
	bool directed;
	boost::optional<bool> weighted;
	ifstream fs(file);
	getline(fs, line);
	istringstream sh(line);
	
	int _dtmp;
	if (!(sh >> _dtmp))
	{
		cerr << "Unable to parse input file: need 0 or 1 in first line indicating whether the graph is directed." << endl;
		return;
	}
	else
	{
		directed = _dtmp == 1;
	}

	int _wtmp;
	if (!(!(sh >> _wtmp)))
	{
		weighted = _wtmp == 1;
	}

	vector<tuple<int, int, int>> el;
	set<int> vr;

	while (getline(fs, line))
	{
		istringstream ss(line);
		int src, dst, weight = 0;

		if (!(ss >> src >> dst))
		{
			break;
		}

		if (weighted.is_initialized())
		{
			if (weighted.get())
			{
				if (!(ss >> weight))
				{
					cerr << "Unable to parse input file: graph is weighted but no weight is specified for " << src << " -> " << dst << "." << endl;
					return;
				}
			}
		}
		else
		{
			weighted = !(!(ss >> weight));
		}

		if (vr.count(src) == 0)
		{
			vr.emplace(src);
		}

		if (vr.count(dst) == 0)
		{
			vr.emplace(dst);
		}

		el.push_back(make_tuple(src, dst, weight));
	}

	init(directed, weighted.get_value_or(false), vr.size(), el.size(), el);
}

Graph::Graph(bool directed, bool weighted, int vertCnt, int edgeCnt, std::vector<std::tuple<int, int, int>> edgeList)
{
	init(directed, weighted, vertCnt, edgeCnt, edgeList);
}

void Graph::init(bool directed, bool weighted, int vertCnt, int edgeCnt, std::vector<std::tuple<int, int, int>> edgeList)
{
	using namespace std;

	cout << "Initializing graph..." << endl << endl;

	this->directed = directed;
	this->weighted = weighted;
	this->vertCnt  = vertCnt;
	this->edgeCnt  = edgeCnt;

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
		int src, dst, weight;
		tie(src, dst, weight) = edgeList[i];

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

Graph* Graph::getCloned()
{
	std::vector<std::tuple<int, int, int>> el;

	for (Edge* edge : edges)
	{
		el.push_back(std::make_tuple(edge->src->id, edge->dst->id, edge->weight));
	}

	return new Graph(directed, weighted, vertCnt, edgeCnt, el);
}

Graph* Graph::getTransposed()
{
	std::vector<std::tuple<int, int, int>> el;

	for (Edge* edge : edges)
	{
		el.push_back(std::make_tuple(edge->dst->id, edge->src->id, edge->weight));
	}

	return new Graph(directed, weighted, vertCnt, edgeCnt, el);
}