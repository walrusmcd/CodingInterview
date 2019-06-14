#include <iostream>
#include <map>
#include <vector>
#include <list>

using namespace std;

class Node
{
public:
	int key;
	vector<Node> children;
};

class Graph
{
public:
	vector<Node> nodes;
};

const Node* dfsSearch(const Node& head, int findKey)
{
	const Node* found = nullptr;
	for (auto it = head.children.begin(); it != head.children.end(); ++it)
	{
		// did we find it?
		if (it->key == findKey)
			return &(*it);
		// keep going !
		found = dfsSearch(*it, findKey);
		if (found != nullptr)
		{
			// we found it!
			return found;
		}
	}
	// if we made it this far, we didn't find it
	return nullptr;
}

const Node* dfsSearchR(Graph g, int startNode, int findKey)
{
	return dfsSearch(g.nodes[startNode], findKey);
}

const Node* dfsSearchI(Graph g, int startNode, int findKey)
{
	// use push/pop on the front of this list to make it a stack.
	list<Node> stack;
	stack.push_front(g.nodes[startNode]);
	while (!stack.empty())
	{
		Node n = stack.front();
		stack.pop_front();
		// is this our node?
		if (n.key == findKey)
		{
			return &n;
		}
		// add all the children to search next.
		for (auto it = n.children.begin(); it != n.children.end(); ++it)
		{
			stack.push_front(*it);
		}
	}
	return nullptr;
}

