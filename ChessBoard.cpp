#include "pch.h"

#include "vector"
#include "utility" // get<>, pair
#include "map"	   // map
#include "cstdlib" // rand
#include "ctime"   // time

using namespace std;

// 0 == x, 1 == y
typedef pair< uint64_t, uint64_t> point;

list<point> getNextMoves(point start)
{
	list<point> output;
	// the knight can move 8 spots, starting frmo the top go clockwise
	output.push_back(point(get<0>(start) + 1, get<1>(start) + 2));
	output.push_back(point(get<0>(start) + 2, get<1>(start) + 1));
	output.push_back(point(get<0>(start) + 2, get<1>(start) - 1));
	output.push_back(point(get<0>(start) + 1, get<1>(start) - 2));
	output.push_back(point(get<0>(start) - 1, get<1>(start) - 2));
	output.push_back(point(get<0>(start) - 2, get<1>(start) - 1));
	output.push_back(point(get<0>(start) - 2, get<1>(start) + 1));
	output.push_back(point(get<0>(start) - 1, get<1>(start) + 2));
	// all done
	return output;
}

bool blockRandom = false;
map<point, bool> blockedMoves;
bool isMoveBlocked(point move)
{
	// TODO: put code in here to block moves
	if (blockRandom)
		return (rand() % 2) == 0;

	if (blockedMoves.find(move) != blockedMoves.end())
		return true;

	return false;
}

// use bfs to find the path of the knight (first attempt)
// we can optimize this later with other techniques like bidi bfs, dijkstra, etc (see below)
list<point> shortestPathKnightBfs(point start, point end, uint32_t maxMovesToTry, uint32_t& movesTried)
{
	bool found = false;
	// keep track of where we have been
	map<point, bool> visited;
	// a list can do FIFO behaviour
	list<point> queue;
	// keep track of our path
	map<point, point> prev;
	// start from the beginning
	queue.push_back(start);
	// start iterating !
	movesTried = 0;
	while (!queue.empty() && !found && movesTried < maxMovesToTry)
	{
		point node = queue.front();
		queue.pop_front();
		// visit the node and bump the move count
		visited[node] = true;
		movesTried += 1;
		// did we find it?
		if (node == end)
		{
			// yup !
			found = true;
		}
		else
		{
			// look in all the children
			list<point> nextMoves = getNextMoves(node);
			for (auto it = nextMoves.begin(); it != nextMoves.end(); ++it)
			{
				// is this a valid move ?
				if (isMoveBlocked(*it) == false &&
					// have we never visited it yet?
					visited.find(*it) == visited.end())
				{
					// remember how we got there
					prev[*it] = node;
					// and go visit it next
					queue.push_back(*it);
				}
			}
		}
	}

	// now construct the path to the end (if we found one)
	point dest = end;
	list<point> path;
	while (found && !(dest == start))
	{
		path.push_front(dest);
		dest = prev[dest];
	}
	if (path.empty() == false)
	{
		path.push_front(start);
	}
	return path;
}

// use djikstra to find the path of the knight (note: i grabbed some of this from my personal djikstra impl in this same repo)
list<point> shortestPathKnightDj(point start, point end, uint32_t maxMovesToTry, uint32_t& movesTried)
{
	// nice trick to use a std::priority_queue sorted by distTo and keeping my vertex
	class QueueItem
	{
	public:
		point vertex;
		uint32_t distTo;
		QueueItem(point vertex, uint32_t distTo)
		{
			this->vertex = vertex;
			this->distTo = distTo;
		}
		constexpr bool operator>(const QueueItem& _Right) const
		{	// apply operator> to operands
			return (this->distTo > _Right.distTo);
		}
	};

	bool found = false;
	// keep track of where we have been
	map<point, bool> visited;
	// use a priority queue with djikstra
	priority_queue<QueueItem, std::vector<QueueItem>, std::greater<QueueItem>> queue;
	// keep track of our path
	map<point, point> prev;
	map<point, uint32_t> distTo;
	// start from the beginning
	distTo[start] = 0;
	queue.push(QueueItem(start, 0));
	// start iterating !
	movesTried = 0;
	while (!queue.empty() && !found && movesTried < maxMovesToTry)
	{
		// pick the vertext with the closest distance
		QueueItem closest = queue.top();
		queue.pop();
		// was it already visited?   note: we have dead items in the PQ since it's not editable
		if (visited.find(closest.vertex) != visited.end())
			continue;
		// visit the node and bump the move count
		visited[closest.vertex] = true;
		movesTried += 1;
		// did we find it?
		if (closest.vertex == end)
		{
			// yup !
			found = true;
		}
		else
		{
			// look in all the children
			list<point> nextMoves = getNextMoves(closest.vertex);
			for (auto it = nextMoves.begin(); it != nextMoves.end(); ++it)
			{
				// what's the new weighted distance from here to there?
				uint32_t newDist = distTo[closest.vertex] + 1;

				// is this a valid move ?
				if (isMoveBlocked(*it) == false)
				{
					auto d = distTo.find(*it);
					// is this a new shortest path?
					if (d == distTo.end() ||
						newDist < d->second)
					{
						// remember how we got there
						distTo[*it] = newDist;
						prev[*it] = closest.vertex;
						// stl doesn't let you modify it's PQ.   always insert.  we will have potential 
						// dead items, the sort will keep the smallest ones the top
						queue.push(QueueItem(*it, newDist));
					}
				}
			}
		}
	}

	// now construct the path to the end (if we found one)
	point dest = end;
	list<point> path;
	while (found && !(dest == start))
	{
		path.push_front(dest);
		dest = prev[dest];
	}
	if (path.empty() == false)
	{
		path.push_front(start);
	}
	return path;
}
void printList(list<point> path)
{
	if (path.empty())
	{
		cout << "path.size = 0\n";
	}
	else
	{
		cout << "path.size = " << path.size() << " ";
		for (auto it = path.begin(); it != path.end(); ++it)
		{
			cout << "(" << get<0>(*it) << "," << get<1>(*it) << ") ";
		}
	}
	cout << "\n";
}

void testChessBoard()
{
	uint32_t movesTried;
	list<point> pathTo;

	srand((unsigned int)std::time(nullptr)); // use current time as seed for random generator

	// a short and easy one
	cout << "shortestPathKnight(100,100 -> 101,102)\n";
	pathTo = shortestPathKnightBfs(make_pair(100, 100), make_pair(101, 102), 1000000, movesTried);
	cout << "\tpath = ";
	printList(pathTo);
	cout << "\tmovesTried = " << movesTried << "\n";

	// one that cannot be hit
	blockedMoves[make_pair(101, 101)] = true;
	cout << "shortestPathKnightd(100,100 -> 101,101)\n";
	pathTo = shortestPathKnightDj(make_pair(100, 100), make_pair(101, 101), 10000, movesTried);
	cout << "\tpath = ";
	printList(pathTo);
	cout << "\tmovesTried = " << movesTried << "\n";
	blockedMoves.clear();

	// a long one 
	cout << "shortestPathKnightd(100,100 -> 140,180)\n";
	pathTo = shortestPathKnightDj(make_pair(100, 100), make_pair(140, 180), 1000000, movesTried);
	cout << "\tpath = ";
	printList(pathTo);
	cout << "\tmovesTried = " << movesTried << "\n";
}