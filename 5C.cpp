#include <iostream>
#include <vector>
#include <list>
#include <limits.h>
#include <algorithm>
#include <set>
#include <unordered_map>

using namespace std;

int const N = 100100;
int const K = 30;

vector<int> level(N,0);
vector<int> parent(N,0);
vector<int> colors(N,0);
vector<vector<int>> graph(N);
vector<unordered_map<int,int>> minLengthsToColor(N);
int lengthsFromCenter[K][N];

int dfs(int v, int size, int &center, int p = -1)
{
	int sum = 1;
	for (auto u : graph [v])
		if (level[u] == -1 && u != p)
			sum += dfs(u, size, center, v);

	if (center == -1 && (2 * sum >= size || p == -1))
		center = v;

	return sum;
}

int length = -1;
void calc(int v, int center, int p = -1)
{
	length++;
	lengthsFromCenter[level[center]][v] = length;
	auto it = minLengthsToColor[center].find(colors[v]);

	if (it == minLengthsToColor[center].end())
	{
		minLengthsToColor[center][colors[v]] = length;
	}
	else if (it->second > length)
	{
		it->second = length;
	}

	for (auto u : graph [v])
	{
		if (level[u] == -1 && u != p)
		{
			calc(u, center, v);
		}
	}
	length--;
}


void build(int v, int size, int depth, int last)
{
	int center = -1;
	dfs (v, size, center);
	level[center] = depth;
	parent[center] = last;
	calc(center, center);
	for (auto u : graph[center])
		if (level[u] == -1)
			build(u, size / 2, depth + 1, center);
};

int main()
{
	freopen("in", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n = 0;
	cin >> n;
	int node;
	for(int i = 1; i < n; i++)
	{
		cin >> node;
		graph[node].push_back(i);
		graph[i].push_back(node);
	}

	for(int i = 0; i < n; i++)
	{
		cin >> colors[i];
		level[i] = -1;
	}

	build (0, n, 0, -1);

	int q;
	cin >> q;
	int v, color;

	for(int i = 0; i < q; i++)
	{
		cin >> v >> color;
		int v1 = v;
		int minimum = INT_MAX;
		int s = 0;
		while(v != -1)
		{
			auto it = minLengthsToColor[v].find(color);
			if (it != minLengthsToColor[v].end())
				minimum = min(minimum, it->second + s);

			v = parent[v];
			if(v != -1)
				s = lengthsFromCenter[level[v]][v1];
		}
		cout << (minimum == INT_MAX ? -1 : minimum) << endl;
	}
}
