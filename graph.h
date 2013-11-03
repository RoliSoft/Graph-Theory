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
	bool directed; // ir�ny�tatotts�g
	bool weighted; // s�lyozotts�g
	int vertices; // cs�csok sz�ma
	int edges; // �lek sz�ma
	std::map<int, Vertex*> verts; // cs�cslista [Ki_SzL, Be_SzL, KiBe_SzL]
	std::vector<Edge*> nums; // �llista [ElL]
	Matrix<bool> matrix; // szomsz�ds�gi m�trix [SzM]
	Matrix<int> watrix; // s�lyozott szomsz�ds�gi m�trix [SulyM]

	Graph(std::string file);

	void depthFirstSearch();
	void breathFirstSearch();

	~Graph();
};

#endif