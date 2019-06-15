// CodingInterview.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "TreesAndGraphs.h"

int main()
{
	char str[1024];

	// 
	std::cout << "isUnique('abcd')   = \t" << isUnique("abcd") << "\n";
	std::cout << "isUnique('abcda')  = \t" << isUnique("abcda") << "\n";
	std::cout << "isUnique('')       = \t" << isUnique("") << "\n";
	std::cout << "isUnique(nullptr)  = \t" << isUnique(nullptr) << "\n";
	std::cout << "\n";
	//
	std::cout << "isUnique2('abcd')  = \t" << isUnique2("abcd") << "\n";
	std::cout << "isUnique2('abcda') = \t" << isUnique2("abcda") << "\n";
	std::cout << "isUnique2('')      = \t" << isUnique2("") << "\n";
	std::cout << "isUnique2(nullptr) = \t" << isUnique2(nullptr) << "\n";
	std::cout << "\n";
	// 
	std::cout << "checkPermutation('dog', 'god') = \t" << checkPermutation("dog", "god") << "\n";
	std::cout << "checkPermutation('dog', 'god1') = \t" << checkPermutation("dog", "god1") << "\n";
	std::cout << "checkPermutation('dog', 'gog') = \t" << checkPermutation("dog", "gog") << "\n";
	std::cout << "checkPermutation('hero', 'eroh') = \t" << checkPermutation("hero", "eroh") << "\n";
	std::cout << "\n";
	//
	strcpy_s(str, sizeof(str), "this is a test");
	std::cout << "URLify('this is a test') = " << URLify(str, strlen(str)) << "\n";
	strcpy_s(str, sizeof(str), "thisisatest");
	std::cout << "URLify('thisisatest') = " << URLify(str, strlen(str)) << "\n";
	strcpy_s(str, sizeof(str), " thisisatest ");
	std::cout << "URLify(' thisisatest ') = " << URLify(str, strlen(str)) << "\n";
	std::cout << "\n";


	// test out some graphs
	EdgeWeightedDirectedGraph g(6);
	g.addEdge(0, 5);
	g.addEdge(0, 4);
	g.addEdge(0, 1);
	g.addEdge(1, 3);
	g.addEdge(1, 4);
	g.addEdge(2, 1);
	g.addEdge(3, 2);
	g.addEdge(3, 4);

	std::cout << "routeBetweenNodes(1,4) = " << routeBetweenNodes(g, 1, 4) << "\n";
	std::cout << "routeBetweenNodes(2,5) = " << routeBetweenNodes(g, 2, 5) << "\n";
	std::cout << "routeBetweenNodes(1,5) = " << routeBetweenNodes(g, 1, 5) << "\n";
	std::cout << "routeBetweenNodes(3,1) = " << routeBetweenNodes(g, 3, 1) << "\n";


	EdgeWeightedDirectedGraph g2(8);
	g2.addEdge(0, 2);
	g2.addEdge(0, 4);
	g2.addEdge(1, 2);
	g2.addEdge(1, 6);
	g2.addEdge(1, 5);
	g2.addEdge(2, 6);
	g2.addEdge(6, 7);
	g2.addEdge(7, 3);

	auto topoList = topologicalSort(g2);
	std::cout << "topologicalSort(g2) = (";
	for (auto it = topoList.begin(); it != topoList.end(); ++it)
	{
		std::cout << *it << ",";
	}
	std::cout << ")\n";

	{
		auto path = shortestPath(g2, 0, 1);
		std::cout << "shortestPath(0, 1) = (";
		for (auto it = path.begin(); it != path.end(); ++it)
		{
			std::cout << *it << ",";
		}
		std::cout << ")\n";
	}

	{
		auto path = shortestPath(g2, 0, 7);
		std::cout << "shortestPath(0, 7) = (";
		for (auto it = path.begin(); it != path.end(); ++it)
		{
			std::cout << *it << ",";
		}
		std::cout << ")\n";
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
