
#include <limits.h>
#include <iostream>
#include <vector>
#include <cfloat>
#include <math.h>
#include <iomanip>
#include <utility>
#include <set>


using namespace std;

struct Edge {
	Edge(long f, long cost):
		f(f),
		cost(cost)
		{}

	long f;
	long cost;
};
int main()
{
	// freopen("in", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	long N,M = 0;
	cin >> N >> M;

	vector<vector<Edge>> graph(N + 1);
	vector<bool> used(N + 1,false);

	long v1,v2 = 0;
	long w = 0;
	for (long i = 0; i < M; i++)
	{
		cin >> v1 >> v2 >> w;
		graph[v1].push_back(Edge(v2,w));
		graph[v2].push_back(Edge(v1,w));
	}

	long long s = 0;
	vector<long> minE(graph.size(), LONG_MAX);
	minE[1] = 0;
	set < pair<long,long> > q;
	q.insert (make_pair (0, 1));

	for(long i = 1; i <= N; i++)
	{
		long vMin = q.begin()->second;
		used[vMin] = true;
		q.erase(q.begin());
		// cout << vMin << ' ' << minE[vMin] << "| ";

		s += minE[vMin];

		for(auto u : graph[vMin])
		{
			if(!used[u.f] && u.cost < minE[u.f])
			{
				q.erase(make_pair(minE[u.f], u.f));
				minE[u.f] = u.cost;
				q.insert(make_pair(minE[u.f], u.f));
			}
		}
	}

	// for(int i = 1; i <= N; i++)
	// 	cout << minE[i] << ' ';
	// cout << endl;
	cout << s << '\n';

	return 0;
}

