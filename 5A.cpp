
#include <iostream>
#include <vector>
#include <list>
#include <limits.h>
#include <algorithm>
#include <set>

using namespace std;
int size = 50000;
int n, l;
vector < vector<int> > g(size, vector<int>());
vector<int> tin(size), tout(size);

int timer = 0;
vector < vector<int> > up(size);

void dfs (int v, int p = 0)
{
	tin[v] = ++timer;
	up[v][0] = p;
	for (int i=1; i<=l; ++i)
		up[v][i] = up[up[v][i-1]] [i-1];

	for (size_t i=0; i < g[v].size(); ++i)
	{
		int to = g[v][i];
		if (to != p)
			dfs (to, v);
	}
	tout[v] = ++timer;
}

bool upper (int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca (int a, int b) {
	if (upper (a, b))
		return a;
	if (upper (b, a))
		return b;
	for (int i=l; i>=0; --i)
		if (! upper (up[a][i], b))
			a = up[a][i];
	return up[a][0];
}

int main()
{
	// freopen("in", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n,m = 0;
	cin >> n;
	int node;
	for(int i = 2; i <= n; i++)
	{
		cin >> node;
		node;
		g[node-1].push_back(i-1);
	}
	// for (int i = 0; i < n; i++)
	// {
	// 	cout << i << " ";
	// 	for (auto u : g[i])
	// 	{
	// 		cout << u << " ";
	// 	}
	// 	cout << endl;
	// }

	l = 1;
	while ((1<<l) <= n)
		++l;

	for (int i=0; i<n; ++i)
		up[i].resize (l+1);

	dfs (0);

	cin >> m;
	int a, b; // текущий запрос
	for(int i = 0; i < m; i++)
	{
		cin >> a >> b;
		cout << lca(a-1, b-1) + 1 << endl;
	}

}
