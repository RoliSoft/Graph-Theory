#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <limits>
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
		cerr << "  Unable to parse input file:" << endl << "    Need 0 or 1 in first line indicating whether the graph is directed." << endl << endl;
		return;
	}
	else
	{
		directed = _dtmp == 1;
		cout << "  Graph explicitly set to be " << (!directed ? "not " : "") << "directed." << endl;
	}

	int _wtmp;
	if (!(!(sh >> _wtmp)))
	{
		weighted = _wtmp == 1;
		cout << "  Graph explicitly set to be " << (!weighted ? "not " : "") << "weighted." << endl;
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
					cerr << "  Unable to parse input file:" << endl << "    Graph is weighted but no weight is specified for " << src << " -> " << dst << "." << endl << endl;
					return;
				}
			}
		}
		else
		{
			weighted = !(!(ss >> weight));
			cout << "  Graph implicitly set to be " << (!weighted.get_value_or(false) ? "not weighted." : "weighted due to weight on " + to_string(src) + " -> " + to_string(dst)) << endl;
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

	cout << endl;

	init(directed, weighted.get_value_or(false), vr.size(), el);
}

Graph::Graph(bool directed, bool weighted, int vertCnt, const std::vector<std::tuple<int, int, int>>& edgeList)
{
	init(directed, weighted, vertCnt, edgeList);
}

void Graph::init(bool directed, bool weighted, int vertCnt, const std::vector<std::tuple<int, int, int>>& edgeList)
{
	using namespace std;

	cout << "Initializing graph..." << endl << endl;

	this->directed = directed;
	this->weighted = weighted;

	cout << " Number of vertices: " << vertCnt << "; edges: " << edgeList.size() << "; graph is " << (!directed ? "not " : "") << "directed and " << (!weighted ? "not " : "") << "weighted." << endl << endl;

	verts  = map<int, Vertex*>();
	edges  = set<Edge*, Edge::less>();
	matrix = boost::numeric::ublas::matrix<bool>(vertCnt + 1, vertCnt + 1, false);

	if (weighted)
	{
		weightrix = boost::numeric::ublas::matrix<int>(vertCnt + 1, vertCnt + 1, INT_MAX);
	}

	for (int i = 0; i < (int)edgeList.size(); i++)
	{
		int src, dst, weight;
		tie(src, dst, weight) = edgeList[i];

		if (!directed)
		{
			if (src > dst)
			{
				swap(src, dst);
			}
		}

		if (!verts.count(src))
		{
			verts.emplace(src, new Vertex(this, src));
		}

		if (!verts.count(dst))
		{
			verts.emplace(dst, new Vertex(this, dst));
		}

		auto edge = new Edge(verts[src], verts[dst], weight);

		cout << "  " << edge->src->id << " " << (!directed ? "<" : "") << "-" << (weighted ? "[" + to_string(edge->weight) + "]" : "") << "-> " << edge->dst->id << endl;

		if (!addEdge(edge))
		{
			cout << "   ^ Failed to add edge!" << endl;
		}
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

	int start = (*verts.begin()).first;

	cout << endl << " Adjacency matrix:" << endl;
	print(matrix, false, start);

	if (weighted)
	{
		cout << " Weighted adjacency matrix:" << endl;
		print(weightrix, INT_MAX, start);
	}
}

bool Graph::addEdge(Edge* edge)
{
	if (!edges.emplace(edge).second)
	{
		return false;
	}

	edge->src->out.emplace(edge);
	edge->dst->in.emplace(edge);
	edge->src->deg.emplace(edge);
	edge->dst->deg.emplace(edge);

	if (!directed)
	{
		edge->dst->out.emplace(edge);
		edge->src->in.emplace(edge);
	}

	matrix.insert_element(edge->src->id, edge->dst->id, true);
	matrix.insert_element(edge->src->id, edge->src->id, true);
	matrix.insert_element(edge->dst->id, edge->dst->id, true);

	if (!directed)
	{
		matrix.insert_element(edge->dst->id, edge->src->id, true);
	}

	if (weighted)
	{
		weightrix.insert_element(edge->src->id, edge->dst->id, edge->weight);
		weightrix.insert_element(edge->src->id, edge->src->id, 0);
		weightrix.insert_element(edge->dst->id, edge->dst->id, 0);

		if (!directed)
		{
			weightrix.insert_element(edge->dst->id, edge->src->id, edge->weight);
		}
	}

	return true;
}

bool Graph::removeEdge(Edge* edge)
{
	if (edges.erase(edge) == 0)
	{
		return false;
	}

	edge->src->out.erase(edge);
	edge->dst->in.erase(edge);
	edge->src->deg.erase(edge);
	edge->dst->deg.erase(edge);

	matrix.insert_element(edge->src->id, edge->dst->id, false);

	if (!directed)
	{
		matrix.insert_element(edge->dst->id, edge->src->id, false);
	}

	if (weighted)
	{
		weightrix.insert_element(edge->src->id, edge->dst->id, INT_MAX);

		if (!directed)
		{
			weightrix.insert_element(edge->dst->id, edge->src->id, INT_MAX);
		}
	}

	return true;
}

Graph* Graph::getCloned()
{
	std::vector<std::tuple<int, int, int>> el;

	for (Edge* edge : edges)
	{
		el.push_back(std::make_tuple(edge->src->id, edge->dst->id, edge->weight));
	}

	return new Graph(directed, weighted, verts.size(), el);
}

Graph* Graph::getTransposed()
{
	std::vector<std::tuple<int, int, int>> el;

	for (Edge* edge : edges)
	{
		el.push_back(std::make_tuple(edge->dst->id, edge->src->id, edge->weight));
	}

	return new Graph(directed, weighted, verts.size(), el);
}

template <typename T> void Graph::print(boost::numeric::ublas::matrix<T>& matrix, T def, int start)
{
	using namespace std;

	cout << endl;

	for (int i = start; i < (int)matrix.size1(); i++)
	{
		if (i == start)
		{
			cout << "  " << left << setw(4) << (def == numeric_limits<T>::max() ? "inf" : " " + to_string(def)) << right;

			for (int j = start; j < (int)matrix.size2(); j++)
			{
				cout << setw(3) << j << " ";
			}

			cout << endl << "     +";

			for (int j = start; j < (int)matrix.size2(); j++)
			{
				cout << " -- ";
			}

			cout << endl;
		}

		cout << "  " << setw(2) << i << " |";

		for (int j = start; j < (int)matrix.size2(); j++)
		{
			auto val = matrix.at_element(i, j);

			if (val == def)
			{
				cout << "  - ";
			}
			else
			{
				cout << setw(3) << val << " ";
			}
		}

		cout << endl;
	}

	cout << endl;
}
