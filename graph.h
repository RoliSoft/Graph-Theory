#ifndef GRAPH_H
#define GRAPH_H

#include "map"
#include "vector"
#include "string"
#include "vertex.h"
#include "edge.h"
#include "matrix.h"

class Graph
{
public:
	bool directed; // irányítatottság
	bool weighted; // súlyozottság
	int vertices; // csúcsok száma
	int edges; // élek száma
	std::map<int, Vertex*> verts; // csúcslista [Ki_SzL, Be_SzL, KiBe_SzL]
	std::vector<Edge*> nums; // éllista [ElL]
	Matrix<bool> matrix; // szomszédsági mátrix [SzM]
	Matrix<int> watrix; // súlyozott szomszédsági mátrix [SulyM]

	Graph(std::string file);

	void depthFirstSearch();
	void breathFirstSearch();

	~Graph();
};

#endif