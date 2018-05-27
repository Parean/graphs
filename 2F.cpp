
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <limits.h>
#include <utility>

struct Edge {
	Edge(int end, long long cost):
		end(end),
		cost(cost)
		{}

	int end;
	long long cost;
};
using namespace std;

void dijkstra(vector<long long> &dist, vector<int> &parents, set<pair <long long,int> > &used, vector< list<Edge> > &graph, int start)
{
	dist[start] = 0;
	used.insert(make_pair(0,start));

	while(!used.empty())
	{
		auto currentPair = *used.begin();
		used.erase(used.begin());

		if(currentPair.first == LONG_LONG_MAX)
			break;

		for(auto e : graph[currentPair.second])
		{
			if(dist[e.end] > currentPair.first + e.cost)
			{
				if(dist[e.end] != LONG_LONG_MAX)
					used.erase(used.find(make_pair(dist[e.end], e.end) ));

				dist[e.end] = currentPair.first + e.cost;
				used.insert(make_pair(dist[e.end], e.end));
				parents[e.end] = currentPair.second;
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N,M,S,F = 0;
	cin >> N >> M >> S >> F;
	vector<list<Edge>> graph(N + 1);

	int v1, v2 = 0;
	long long w = 0;
	for (int i = 0; i < M; i++)
	{
		cin >> v1 >> v2 >> w;
		graph[v1].push_back(Edge(v2,w));
		graph[v2].push_back(Edge(v1,w));
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

	vector<long long> dist(N + 1, LONG_LONG_MAX);
	set<pair <long long,int> > used;
	vector<int> parents(N + 1, -1);
	dijkstra(dist, parents, used, graph, S);
	// for(int i = 1; i<graph.size(); i++)
	// {
	// 	cout << dist[i] << ' ';
	// }
	// cout<<endl;
	if (dist[F] != LONG_LONG_MAX)
	{

		cout << dist[F] << ' ' << '\n';
	}
	else
	{
		cout << -1 << '\n';
	}

	return 0;
}

