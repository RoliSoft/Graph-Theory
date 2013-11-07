#include <iostream>
#include "algo.h"

GraphAlgo::GraphAlgo(Graph* graph)
	: graph(graph)
{
	if (graph == nullptr)
	{
		std::cerr << "Warning: nullptr specified to " << typeid(this).name() << "!" << std::endl;
	}
}