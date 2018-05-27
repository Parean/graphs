


#include <iostream>
#include <vector>
#include <list>
#include <limits.h>
#include <deque>
#include <utility>
#include <map>

struct Edge {
	Edge(int end, long long cost):
		end(end),
		cost(cost)
		{}

	int end;
	long long cost;
};
using namespace std;
deque<int> q;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N,M,s,t = 0;
	cin >> N >> M;
	vector<vector<Edge>> graph(N + 1);

	int v1, v2 = 0;
	long long w = 0;
	for (int i = 0; i < M; i++)
	{
		cin >> v1 >> v2 >> w;
		graph[v1].push_back(Edge(v2,w));
	}
	vector<long long> dist(N + 1, LONG_LONG_MAX);
	vector<bool> inQueue(N + 1, false);
	int k = 0;
	int from = 0;
	int to = 0;
	cin >> k;

	for(int i = 0; i < k; i++)
	{
		cin >> from >> to;

		q.push_back(from);
		dist[from] = 0;

		while (!q.empty())
		{
			int v = q.front();
			q.pop_front();
			inQueue[v] = false;

			for (auto e : graph[v])
			{
				if (dist[e.end] > dist[v] + e.cost)
				{
					dist[e.end] = dist[v] + e.cost;
					if (!inQueue[e.end])
					{
						if (!q.empty() && dist[e.end] < dist[q.front()])
                        	q.push_front(e.end);
						else
							q.push_back(e.end);
						inQueue[e.end] = true;
					}
				}
			}
		}

		if(dist[to] == LONG_LONG_MAX)
			cout << (-1) << '\n';
		else
		{
			cout << (dist[to]) << '\n';
		}
		for (int i = 1; i < graph.size(); i++)
			dist[i] = LONG_LONG_MAX;
	}


	return 0;
}

