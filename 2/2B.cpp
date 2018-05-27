
#include <iostream>
#include <vector>
#include <list>
#include <limits.h>
#include <algorithm>

struct Edge {
	Edge(int s, int f, long long cost):
		s(s),
		f(f),
		cost(cost)
		{}

	int s, f;
	long long cost;
};

using namespace std;

void dfs(
	vector<bool> &isReachableFromCycle,
	vector< list<int> > &graph,
	int v
)
{
	isReachableFromCycle[v] = true;
	for(auto u: graph[v])
	{
		if (!isReachableFromCycle[u])
			dfs(isReachableFromCycle, graph, u);
	}
}

void fordBellman(
	vector<long long> &dist,
	list<Edge> &ES,
	vector< list<int> > &graph,
	vector<bool> &isReachableFromCycle,
	int begin
)
{
	int N = graph.size() - 1;
	dist[begin] = 0;
	bool isEnd = false;

	for (int i = 0; i < N - 1; i++)
	{
		if(isEnd)
			break;

		isEnd = true;
		for(auto e : ES)
		{
			if(dist[e.s] < LONG_LONG_MAX && dist[e.f] > dist[e.s] + e.cost)
			{
				dist[e.f] = max(-LONG_LONG_MAX, dist[e.s] + e.cost);
				isEnd = false;
			}
		}
	}

	vector<int> cycleVs;
	for(auto e : ES)
	{
		if(dist[e.s] < LONG_LONG_MAX && dist[e.f] > dist[e.s] + e.cost)
		{
			dist[e.f] = max(-LONG_LONG_MAX, dist[e.s] + e.cost);
			cycleVs.push_back(e.f);
		}
	}

	for(auto v : cycleVs)
	{
		if(!isReachableFromCycle[v])
			dfs(isReachableFromCycle, graph, v);
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N,M,begin = 0;
	cin >> N >> M >> begin;
	list<Edge> ES;
	vector<list <int> > graph(N + 1);

	int v1, v2 = 0;
	long long cost = 0;
	for (int i = 0; i < M; i++)
	{
		cin >> v1 >> v2 >> cost;
		graph[v1].push_back(v2);
		ES.push_back(Edge(v1,v2,cost));
	}

	vector<long long> dist(N + 1, LONG_LONG_MAX);
	vector<bool> isReachableFromCycle(N + 1, false);
	fordBellman(dist, ES, graph, isReachableFromCycle, begin);

	for(int i = 1; i <= N; i++)
	{
		if (dist[i] == LONG_LONG_MAX)
		{
			cout << "*\n";
		}
		else if(isReachableFromCycle[i])
		{
			cout << "-\n";
		}
		else
		{
			cout << dist[i] << '\n';
		}
	}

	return 0;
}

