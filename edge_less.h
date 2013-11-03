#ifndef EDGE_LESS_H
#define EDGE_LESS_H

#include "iostream"
#include "edge.h"

struct edge_less {
	bool operator()(const Edge* lhs, const Edge* rhs) const;
};

#endif