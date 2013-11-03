#include "iostream"
#include "graph.h"

using namespace std;

int main()
{
	cout << "Initializing graph from file..." << endl << endl;
	auto graph1 = Graph("input.txt");
	graph1.depthFirstSearch();

	system("pause");
	return EXIT_SUCCESS;
}