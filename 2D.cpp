
#include <iostream>
#include <vector>
#include <list>
#include <limits.h>
#include <queue>

struct Edge {
	Edge(int end, long long cost):
		end(end),
		cost(cost)
		{}

	int end;
	long long cost;
};

using namespace std;
void spfa(vector<long long> &dist, vector<bool> &inQueue, vector< list<Edge> > &graph, int start)
{
	queue<int> q;
	q.push(start);
	dist[start] = 0;

	while (!q.empty())
	{
        int v = q.front();
		q.pop();
		inQueue[v] = false;

		for (auto e : graph[v])
		{
			if (dist[e.end] > dist[v] + e.cost)
			{
				dist[e.end] = dist[v] + e.cost;
				if (!inQueue[e.end])
				{
					q.push(e.end);
					inQueue[e.end] = true;
				}
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N,M,s,t = 0;
	cin >> N >> M >> s >> t;
	vector<list<Edge>> graph(N + 1);

	int v1, v2 = 0;
	long long w = 0;
	for (int i = 0; i < M; i++)
	{
		cin >> v1 >> v2 >> w;
		graph[v1].push_back(Edge(v2,w));
	}

	vector<long long> dist(N + 1, LONG_LONG_MAX);
	vector<bool> inQueue(N + 1, false);

	spfa(dist, inQueue, graph, s);
	if(dist[t] < LONG_LONG_MAX)
		cout << dist[t]<< endl;
	else
		cout << 1000000000000000000 << endl;

	return 0;
}

