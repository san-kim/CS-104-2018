#include "graph.h"

#include <stack>
#include <queue>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

bool DFS(Node* start, Node* end) 
{
	set<Node*> isVisited;
	stack<Node*> DFSstack;
	DFSstack.push(start);
	isVisited.insert(start);
	while(DFSstack.empty() == false)
	{	
		Node* next = DFSstack.top();
		if(next == end)
		{
			return true;
		}

		DFSstack.pop();

		for(unsigned int i = 0; i< next->neighbors.size(); i++)
		{
			if(next->neighbors[i] == end)
			{
				return true;
			}
			//if not visited yet
			if(isVisited.find(next->neighbors[i]) == isVisited.end())
			{
				DFSstack.push(next->neighbors[i]);
				isVisited.insert(next->neighbors[i]);
			}
		}
	}

	return false;
}


bool BFS(vector<vector<int> > adjacency_matrix, int start, int end) 
{
	set<int> isVisited;
	queue<vector<int> > BFSqueue;
	BFSqueue.push(adjacency_matrix[start]);
	isVisited.insert(start);

	if((unsigned int)end > adjacency_matrix.size())
	{
		return false;
	}

	while(BFSqueue.empty() == false)
	{
		vector<int> next = BFSqueue.front();
		if(next[end] != 0)
		{
			return true;
		}

		BFSqueue.pop();

		for(unsigned int i = 0; i<next.size(); i++)
		{
			//for outgoing edges
			if(next[i] != 0)
			{
				if((int)i == end)
				{
					return true;
				}

				//if not yet visited, skips 0s
				if(isVisited.find(i) == isVisited.end())
				{
					BFSqueue.push(adjacency_matrix[i]);
					isVisited.insert(i);
				}
			}
		}
	}

	return false;
}