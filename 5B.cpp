#include <iostream>
#include <vector>
#include <list>
#include <limits.h>
#include <algorithm>
#include <set>

using namespace std;

struct Edge
{
	Edge(int weight, int v):
		weight(weight),
		v(v)
	{}

	int weight = 0;
	int v = 0;
};
int const N = 60000;
int const K = 30;

int getCenter (int a, int b);
void calc(int v, int depth, int p = -1, int minimum = INT_MAX);
int get(int a, int b);
int dfs(int v, int size, int &center, int p = -1);

int level[N]; // уровень рекурсии, изначально -1
int parent[N]; // отец-центр в декомпозиции
vector<Edge> graph[N]; // соседи для каждой вершины
int f[K][N]; // K = round_up (log 2 (N))

void build(int v, int size, int depth, int last)
{ // size - оценка сверху
	int center = -1;
	dfs (v, size, center); // центр выбирается жадно
	calc(center, depth); // вызов из build
	level[center] = depth;
	parent[center] = last;
	for (auto e : graph[center])
		if (level[e.v] == -1)
			build(e.v, size / 2, depth + 1, center);
};

int dfs(int v, int size, int &center, int p)
{ // выбор центра
	int sum = 1;
	for (auto e : graph [v])
		if (level [e.v] == -1 && e.v != p)
			sum += dfs(e.v, size, center, v);
	if (center == -1 && (2 * sum >= size || p == -1)) // новый случай: дошли до верха
		center = v;

	return sum;
}

int getCenter(int a, int b)
{
	while (level [a] > level [b])
		a = parent [a];
	while (level [a] < level [b])
		b = parent [b];
	while (a != b)
		a = parent [a], b = parent [b];

	return a;
}

void calc(int v, int depth, int p, int minimum)
{
	f[depth][v] = minimum; // depth – уровень центра компоненты, которую мы сейчас обходим
	for (auto e : graph [v])
		if (level[e.v] == -1 && e.v != p)
			calc(e.v, depth, v, min(minimum, e.weight));
}

int get(int a, int b)
{
	int c = getCenter (a, b); // O(LCA), самая долгая часть
	return min(f[level[c]][a], f[level[c]][b]);
}

int main()
{
	freopen("in", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n,m = 0;
	cin >> n;
	int node,w;
	for(int i = 2; i <= n; i++)
	{
		cin >> node >> w;
		graph[node-1].push_back(Edge(w,i-1));
		graph[i-1].push_back(Edge(w,node-1));
	}

	for (int i = 0; i < n; i++)
		level[i] = -1;

	build (0, n, 0, -1); // первый параметр - любая вершина

	cin >> m;
	int a, b; // текущий запрос

	for(int i = 0; i < m; i++)
	{
		cin >> a >> b;
		cout << get(a-1, b-1) << endl;
	}
}
