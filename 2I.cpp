


#include <iostream>
#include <vector>
#include <list>
#include <limits.h>
#include <queue>
#include <set>

using namespace std;
long long ss = 0;
struct Edge {
	Edge(int end, long long cost):
		end(end),
		cost(cost)
		{}

	int end;
	long long cost;
};

void dijkstra(vector<long long> &dist, vector< list<Edge> > &graph, int start)
{
	set<pair <long long,int> > used;
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
			}
		}
	}
}


void buildGraph(int a, int b, int c, vector<list<Edge>> &graph)
{
	vector<bool> used(a,false);
	used[1] = true;

	queue<int> q;
	q.push(1);

	while(!q.empty())
	{
		auto v = q.front();
		q.pop();

		graph[v].push_back(Edge((v + b) % a, b));
		graph[v].push_back(Edge((v + c) % a, c));

		if(!used[(v + b) % a])
		{
			q.push((v + b) % a);
			used[(v + b) % a] = true;
		}

		if(!used[(v + c) % a])
		{
			q.push((v + c) % a);
			used[(v + c) % a] = true;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	long long N = 0;
	int a,b,c = 0;
	cin >> N >> a >> b >> c;
	if(a == 1)
	{
		cout << N << '\n';
		return(0);
	}

	vector<long long> dist(a, LONG_LONG_MAX);
	vector<list<Edge>> graph(a);

	buildGraph(a,b,c,graph);
	dijkstra(dist, graph, 1);

	// for(int i = 0; i<a; i++)
	// {
	// 	cout << i << ' ';
	// 	for(auto e : graph[i])
	// 	{
	// 		cout << '(' << e.end<<','<<e.cost<<')'<<' ';
	// 	}
	// 	cout<<'\n';
	// }

	long long s = 0;
	for(int i = 0; i < a; i++)
	{
		if(dist[i] == LONG_LONG_MAX || dist[i] >= N )
			continue;

		s += (N - (dist[i] + 1)) / a + 1;
	}

	cout << s << '\n';
	return 0;
}

