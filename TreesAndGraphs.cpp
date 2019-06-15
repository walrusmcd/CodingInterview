#include "pch.h"
#include "TreesAndGraphs.h"



bool dfsRecursive(EdgeWeightedDirectedGraph g, int from, int to = -1)
{
	static int recurseCount = 0;
	static std::vector<bool> visited;

	// is this the start?
	if (recurseCount++ == 0)
	{
		// make sure it's the right size
		visited.resize(g.V, false);
		// resize won't reset content, only sets the new items on growth
		std::fill(visited.begin(), visited.end(), 0);
	}
	visited[from] = true;
	// did we find the node we are looking for?
	if (to != -1 && from == to)
	{
		--recurseCount;
		return true;
	}
	// keep looking !
	for (auto it = g.adj[from].begin(); it != g.adj[from].end(); ++it)
	{
		// try this child
		if (!visited[it->to] && dfsRecursive(g, it->to, to))
		{
			--recurseCount;
			return true;
		}
	}
	// not found yet, keep looking
	--recurseCount;
	return false;
}

bool dfsIterative(EdgeWeightedDirectedGraph g, int from, int to = -1)
{
	// keep track of cycles
	std::vector<bool> visited(g.V, false);
	// a list can do LIFO behaviour
	std::list<int> stack;
	// start from the beginning
	stack.push_back(from);
	// start iterating !
	while (!stack.empty())
	{
		int node = stack.back();
		stack.pop_back();
		visited[node] = true;
		// did we find it?
		if (to != -1 && node == to)
		{
			// yup !
			return true;
		}
		// look in all the children
		for (auto it = g.adj[node].begin(); it != g.adj[node].end(); ++it)
		{
			if (!visited[it->to])
				stack.push_back(it->to);
		}
	}
	// didn't find it !
	return false;
}

bool bfsIterative(EdgeWeightedDirectedGraph g, int from, int to = -1)
{
	// keep track of cycles
	std::vector<bool> visited(g.V, false);
	// a list can do FIFO behaviour
	std::list<int> queue;
	// start from the beginning
	queue.push_back(from);
	// start iterating !
	while (!queue.empty())
	{
		int node = queue.front();
		queue.pop_front();
		visited[node] = true;
		// did we find it?
		if (to != -1 && node == to)
		{
			// yup !
			return true;
		}
		// look in all the children
		for (auto it = g.adj[node].begin(); it != g.adj[node].end(); ++it)
		{
			if (!visited[it->to])
				queue.push_back(it->to);
		}
	}
	// didn't find it !
	return false;
}

bool routeBetweenNodes(EdgeWeightedDirectedGraph g, int from, int to)
{
	bool found;

	// first try and do a DFS recursive
	found = dfsRecursive(g, from, to);

	// do a DFS iterative
	if (dfsIterative(g, from, to) != found)
	{
		std::cout << "dfsRecursive said {" << found << "} but dfsIterative() didn't match\n";
		exit(-1);
	}

	// do a BFS iterative
	if (bfsIterative(g, from, to) != found)
	{
		std::cout << "dfsIterative said {" << found << "} but bfsIterative() didn't match\n";
		exit(-1);
	}

	return found;
}

// this uses kahns' method
std::list<int> topologicalSort(EdgeWeightedDirectedGraph g)
{
	std::list<int> order;
	std::list<int> processNext;
	std::vector<int> incoming(g.V, 0);

	// first go and count all of the incoming edges for each node
	for (auto it = g.adj.begin(); it != g.adj.end(); ++it)
	{
		// for each edge
		for (auto it2 = it->begin(); it2 != it->end(); ++it2)
		{
			incoming[it2->to] += 1;
		}
	}

	// now go and find all of the "tops" ; where their inbound's are 0
	for (int i = 0 ; i < incoming.size(); ++i)
	{
		if (incoming[i] == 0)
		{
			// add these to the ordered list 
			processNext.push_back(i);
			incoming[i] = -1;
		}
	}

	// now loop through processNext until done
	while (!processNext.empty())
	{
		// grab the first one
		int n = processNext.front();
		processNext.pop_front();

		// go remove the edge from everyone it points to
		for (auto it = g.adj[n].begin(); it != g.adj[n].end(); ++it)
		{
			incoming[it->to] -= 1;
			// is the last edge?
			if (incoming[it->to] == 0)
			{ 
				// add it to the processing list
				processNext.push_back(it->to);
				incoming[it->to] = -1;
			}
		}

		// add n to the ordered list
		order.push_back(n);
	}

	// did it work?  (cycles will break it)
	if (order.size() != g.V)
	{
		std::cout << "topologicalSort() was passed a graph that has no valid topological sort\n";
		exit(-1);
	}
	return order;
}

// this uses djikstra
std::list<int> shortestPath(EdgeWeightedDirectedGraph g, int from, int to)
{
	class QueueItem
	{
	public:
		int vertex;
		double distTo;
		QueueItem(int vertex, double distTo)
		{
			this->vertex = vertex;
			this->distTo = distTo;
		}
		constexpr bool operator>(const QueueItem& _Right) const
		{	// apply operator> to operands
			return (this->distTo > _Right.distTo);
		}
	};

	std::vector<double> distTo(g.V, std::numeric_limits<double>::infinity());
	std::vector<int> prev(g.V, -1);
	std::vector<bool> green(g.V, false);
	std::priority_queue<QueueItem, std::vector<QueueItem>, std::greater<QueueItem>> yellow;

	distTo[from] = 0.0;
	yellow.push(QueueItem(from, 0.0));

	// go through all of the yellows
	while (!yellow.empty())
	{
		// pick the yellow vertext with the closest distance
		QueueItem closest = yellow.top();
		yellow.pop();

		// was it already green?   note: we have dead items in the PQ since it's not editable
		if (green[closest.vertex])
			continue;

		// mark it green
		green[closest.vertex] = true;

		// go through all of it's children
		for (auto it = g.adj[closest.vertex].begin(); it != g.adj[closest.vertex].end(); ++it)
		{
			// what's the new weighted distance from here to there?
			double newDist = distTo[it->from] + it->weight;
			// is this a smaller distance than what we already found?
			if (newDist < distTo[it->to])
			{
				distTo[it->to] = newDist;
				prev[it->to] = it->from;
				// stl doesn't let you modify it's PQ.   always insert.  we will have potential 
				// dead items, the sort will keep the smallest ones the top
				yellow.push(QueueItem(it->to, newDist));
			}
		}

	}

	// now find the path to the end
	int dest = to;
	std::list<int> path;
	while (prev[dest] != -1)
	{
		path.push_front(dest);
		dest = prev[dest];
	}
	if (!path.empty())
		path.push_front(from);
	return path;
}
