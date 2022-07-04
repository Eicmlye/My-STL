#include <iostream>
#include <vector>
#include "Graph.h"

using std::cout; 
using std::endl; 
using std::vector; 

int main(void)
{
	#if 0
		UDGraph<char, int> graph('A', true);
		for (char index = 'B'; index < 'G'; ++index) {
			graph.insert(index); 
		}

		graph.connect(0, 2, 1);
		graph.connect(1, 2, 2);
		graph.connect(4, 3, 3);
		graph.connect(4, 5, 4);
		graph.connect(3, 5, 5);

		graph.cut(1, 3);

		graph.print(3);
		cout << endl; 
		graph.print();

		cout << std::boolalpha; 

		try {
			cout << graph.isEdge(1, 5) << endl;
		}
		catch (IndexOverflow) {

		}
		cout << graph.isEdge(1, 3) << endl;
		cout << graph.isEdge(0, 2) << endl;
		cout << graph.isEdge(4, 3) << endl;

		if (graph.isWeighted()) {
			cout << graph.getVal(4, 3) << endl;
		}

		cout << graph.getComponentNum() << endl; 
	#endif

	#if 0
		UDGraph<char, int> graph('A', true);
		for (char index = 'B'; index < 'G'; ++index) {
			graph.insert(index);
		}

		graph.connect(0, 1, 6);
		graph.connect(1, 4, 3);
		graph.connect(4, 5, 6);
		graph.connect(3, 5, 2);
		graph.connect(0, 3, 5);

		graph.connect(0, 2, 1);
		graph.connect(1, 2, 5);
		graph.connect(2, 4, 6);
		graph.connect(2, 5, 4);
		graph.connect(2, 3, 5);

		graph.print();
		std::cout << std::endl;

		graph = graph.getMinimalSpanningTree(0, true);
		graph.print();
	#endif

	#if 0
		UDGraph<char, unsigned int> graph('A');
		for (char index = 'B'; index - 'A' < 6; ++index) {
			graph.insert(index);
		}

		graph.connect(0, 1);
		graph.connect(0, 2);
		graph.connect(0, 4);
		graph.connect(1, 4);
		graph.connect(3, 4);
		graph.connect(5, 4);
		graph.connect(5, 3);
		graph.print(); 

		vector<unsigned int> dist = graph.getShortestPathLen(0);
		for (auto i : dist) {
			cout << i << ' '; 
		}
		cout << endl; 
		cout << graph.getShortestPathLen(0, 3) << endl; 
	#endif
	return 0;
}