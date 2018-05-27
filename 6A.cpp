#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <float.h>
#include <vector>
#include <iomanip>
#include <queue>
using namespace std;

class Edge {
	int a, b, to;
	double capacity, flow;
public:
	Edge(int a, int b, double capacity) : a(a), b(b), capacity(capacity), flow(0), to(-1) {}
	int other(int v) const {
		return v == a ? b : a;
	}
	double capacityTo(int v) const {
		return (to == v || to == -1) ? capacity - flow : flow;
	}
	pair<double,bool> getFlow() const {
		return make_pair(flow,to == b);
	}
	double addFlowTo(int v, double f) {
		flow += (v == to || to == -1 ? f : -f);
		to = v;
		return flow;
	}
};

class Graph {
	vector<Edge> edges;
	vector< vector<int> > g;
	vector<bool> used;
	vector<int> edgeTo;
	void bfs(int v) {
		queue<int> q;
		used[v] = 1;
		q.push(v);
		while (!q.empty()) {
			v = q.front();
			q.pop();
			for (int i = 0; i < g[v].size(); i++) {
				int e = g[v][i];
				int to = edges[e].other(v);
				// cout << v << ' ' << to << ' ' << e << ' ' << edges[e].capacityTo(to) << endl;
				if (!used[to] && abs(edges[e].capacityTo(to) > 10e-3)) {
					edgeTo[to] = e;
					used[to] = 1;
					q.push(to);
				}
			}
		}
		// cout << endl;
	}
	bool hasPath(int from, int to) {
		fill(used.begin(), used.end(), 0);
		bfs(from);
		return used[to];
	}
	double bottleneckCapacity(int from, int to) {
		double bCapacity = DBL_MAX;
		for (int v = to; v != from; v = edges[edgeTo[v]].other(v))
			bCapacity = min(bCapacity, edges[edgeTo[v]].capacityTo(v));
		return bCapacity;
	}
	void addFlow(int from, int to, double flow) {
		for (int v = to; v != from; v = edges[edgeTo[v]].other(v))
			edges[edgeTo[v]].addFlowTo(v, flow);
	}

public:
	Graph(int verticesCount) {
		g.resize(verticesCount);
		used.resize(verticesCount);
		edgeTo.resize(verticesCount);
	}


	void printPath(int from,int to)
	{
		for (auto e : edges)
		{
			auto ans = e.getFlow();
			cout << setprecision(3) << fixed << (ans.second ? ans.first : -ans.first) << ' ';
		}
		cout << endl;
	}

	void addEdge(int from, int to, double capacity) {
		edges.push_back(Edge(from, to, capacity));
		g[from].push_back(edges.size() - 1);
		g[to].push_back(edges.size() - 1);
	}
	double maxFlow(int from, int to) {
		double flow = 0;
		while (hasPath(from, to)) {
			double deltaFlow = bottleneckCapacity(from, to);
			addFlow(from, to, deltaFlow);
			flow += deltaFlow;
		}
		return flow;
	}
};


int main() {
	int n, m;
	freopen("in", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	Graph g(n);

	int a, b;
	double c;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		g.addEdge(a - 1, b - 1, c);
	}

	cout.precision(3);
	cout << setprecision(3)<<fixed<<g.maxFlow(0, n - 1) << endl;
	g.printPath(0,n-1);
}
