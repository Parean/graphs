
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <float.h>
#include <vector>
#include <iomanip>
#include <queue>
#include <limits.h>

typedef long long ll;

using namespace std;

class Edge {
public:
	int a, b, to;
	ll capacity, flow, cost;
	Edge(int a, int b, ll capacity, ll cost) : a(a), b(b), capacity(capacity), flow(0), cost(cost) {}

	int other(int v) const {
		return v == a ? b : a;
	}

	ll capacityTo(int v) const {
		return v == b ? capacity - flow : flow;
	}

	ll costTo(int v) const {
		return (v == b) ? cost : -cost;
	}

	pair<ll,bool> getFlow() const {
		return make_pair(flow,to == b);
	}

	ll addFlowTo(int v, ll f) {
		flow += (v == b ? f : -f);
		return flow;
	}
};

class Graph {
	vector<Edge> edges;
	vector< vector<int> > g;
	vector<ll> dist;
	vector<bool> used;
	vector<int> edgeTo;
	vector<int> parents;

	void fordBellman(int begin	)
	{
		dist[begin] = 0;
		bool isEnd = false;

		for (int i = 0; i < dist.size() - 1; i++)
		{
			if(isEnd)
				break;

			isEnd = true;
			for(int i = 0; i < edges.size(); i++)
			{
				auto e = edges[i];
				if(e.capacityTo(e.b) && dist[e.a] < LONG_LONG_MAX && dist[e.b] > dist[e.a] + e.costTo(e.b))
				{
					// cout << i;
					dist[e.b] = max(-LONG_LONG_MAX, dist[e.a] + e.costTo(e.b));
					edgeTo[e.b] = i;
					isEnd = false;
				}
			}

			for(int i = 0; i < edges.size(); i++)
			{
				auto e = edges[i];
				if(e.capacityTo(e.a) && dist[e.b] < LONG_LONG_MAX && dist[e.a] > dist[e.b] + e.costTo(e.a))
				{
					// cout << 88;
					dist[e.a] = max(-LONG_LONG_MAX, dist[e.b] + e.costTo(e.a));
					edgeTo[e.a] = i;
					isEnd = false;
				}
			}
		}
	}

	bool hasPath(int from, int to) {
		fill(used.begin(), used.end(), 0);
		fill(dist.begin(), dist.end(), LONG_LONG_MAX);
		fordBellman(from);
		return dist[to] != LONG_LONG_MAX;
	}

	ll bottleneckCapacity(int from, int to) {
		ll bCapacity = LONG_LONG_MAX;
		for (int v = to; v != from; v = edges[edgeTo[v]].other(v))
			bCapacity = min(bCapacity, edges[edgeTo[v]].capacityTo(v));
		return bCapacity;
	}
	void addFlow(int from, int to, ll flow) {
		for (int v = to; v != from; v = edges[edgeTo[v]].other(v))
			edges[edgeTo[v]].addFlowTo(v, flow);
	}

public:

	Graph(int verticesCount) {
		g.resize(verticesCount);
		parents.resize(verticesCount);
		dist.resize(verticesCount);
		used.resize(verticesCount);
		edgeTo.resize(verticesCount);
	}

	void printPath(int from,int to)
	{
		ll s = 0;
		for (auto e : edges)
		{
			// cout << e.flow << ' ';
			s += e.flow ? e.cost * e.flow : 0;
		}
		cout << s << endl;
	}

	void addEdge(int from, int to, ll capacity, ll cost) {
		edges.push_back(Edge(from, to, capacity, cost));
		g[from].push_back(edges.size() - 1);
		g[to].push_back(edges.size() - 1);
	}
	ll maxFlow(int from, int to) {
		ll flow = 0;
		while (hasPath(from, to)) {
			ll deltaFlow = bottleneckCapacity(from, to);
			addFlow(from, to, deltaFlow);
			flow += deltaFlow;
		}
		return flow;
	}
};



int main() {
	int n, m;
	//freopen("in", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	Graph g(n);

	int a, b;
	ll capacity, cost;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> capacity >> cost;
		g.addEdge(a - 1, b - 1, capacity, cost);
	}

	g.maxFlow(0, n - 1);
	g.printPath(0,n-1);
}
