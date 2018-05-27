
#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int cycle_begin = -1;
int cycle_end = -1;
bool dfs(vector<int> &children, vector<int> &color, vector<bool> &used, vector< list<int> > &graph, int v)
{
	used[v] = true;

	color[v] = 1;
	for(auto i: graph[v])
	{
		if (color[i] == 1)
		{
			cycle_end = v;
			cycle_begin = i;
			return true;
		}

		if (!used[i])
		{
			children[v] = i;
			if (dfs(children, color, used, graph, i))
				return true;
		}
	}
	color[v] = 2;
	return false;
}

int main()
{
	int N,M = 0;
	cin >> N >> M;
	vector< list<int> > graph(N + 1);

	int v1, v2 = 0;
	for (int i = 0; i < M; i++)
	{
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
	}

	vector<bool> used(N + 1, false);
	vector<int> children(N + 1, -1);
	vector<int> color(N + 1, 0);
	for(int i = 1; i <= N; i++)
	{
		if (!used[i])
		{
			if (dfs(children, color, used, graph, i))
				break;

		}
	}

	if (cycle_end != -1)
	{
		cout << "YES" << endl;
		for(int v = cycle_begin; v != cycle_end; v = children[v])
		{
			cout << v << ' ';
		}
		cout << cycle_end << endl;
	}
	else
	{
		cout << "NO" << endl;
	}
	return 0;
}

