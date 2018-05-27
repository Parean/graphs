
#include <iostream>
#include <vector>
#include <list>
#include <limits.h>
#include <deque>

struct Edge {
	Edge(int end, bool cost):
		end(end),
		cost(cost)
		{}

	int end;
	bool cost;
};

using namespace std;
void bfs(vector<int> &dist, vector<int> &parents, vector< list<Edge> > &graph, int start)
{
	deque<int> q;
	q.push_back(start);
	dist[start] = 0;
	int N=graph.size()-1;

	while (!q.empty())
	{
        int v = q.front();
		q.pop_front();

		for (auto e : graph[v])
		{
			if (dist[e.end] > dist[v] + e.cost)
			{
				dist[e.end] = dist[v] + e.cost;
				parents[e.end] = v;
				if (e.cost)
				{
					q.push_back(e.end);
				}
				else
				{
					q.push_front(e.end);
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

	int N,M = 0;
	cin >> N >> M;
	vector<list<Edge>> graph(N + 1);
	vector<int> cities(N + 1);
	for (int i = 1; i <= N; i++)
	{
		cin >> cities[i];
	}

	int v1, v2 = 0;
	for (int i = 0; i < M; i++)
	{
		cin >> v1 >> v2;
		graph[v1].push_back(Edge(v2,cities[v1] != cities[v2]));
		graph[v2].push_back(Edge(v1,cities[v1] != cities[v2]));
	}
	// for(int i = 1; i<=N; i++)
	// {
	// 	cout << i<<' ';
	// 	for(auto e : graph[i])
	// 	{
	// 		cout << '(' << e.end<<','<<e.cost<<')'<<' ';
	// 	}
	// 	cout<<'\n';
	// }

	vector<int> dist(N + 1, INT_MAX);
	vector<int> parents(N + 1, -1);
	bfs(dist, parents, graph, 1);

	if (dist[N] != INT_MAX)
	{
		list<int> path;
		for(int i = N; i != -1; i=parents[i])
		{
			path.push_front(i);
		}

		cout << dist[N] << ' ' << path.size() << '\n';
		for(auto p : path)
		{
			cout << p << ' ';
		}
		cout<<'\n';
	}
	else
	{
		cout << "impossible" << '\n';
	}

	return 0;
}

