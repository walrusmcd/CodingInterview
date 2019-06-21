#pragma once
#include "pch.h"


class DirectedEdge
{
public:
	int from;
	int to;
	double weight;
};

class EdgeWeightedDirectedGraph
{
public:
	int V;
	int E;
	std::vector<std::vector<DirectedEdge>> adj;

	EdgeWeightedDirectedGraph(int V) :
		adj(V)
	{
		this->V = V;
		this->E = 0;
	}

	void addEdge(int from, int to, double weight = 0.0)
	{
		DirectedEdge edge = { from, to, weight };
		this->adj[from].push_back(edge);
	}
};

bool routeBetweenNodes(EdgeWeightedDirectedGraph g, int from, int to);
std::list<int> topologicalSort(EdgeWeightedDirectedGraph g);
std::list<int> shortestPath(EdgeWeightedDirectedGraph g, int from, int to);

class TreeNode
{
public:
	int data;
	TreeNode* left;
	TreeNode* right;
};
void printTreeInOrder(TreeNode* node);
void printTreePostOrder(TreeNode* node);
TreeNode* buildTree();
