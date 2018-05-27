
#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;
bool cycleExists = false;

void dfs(vector<int> &color, list<int> &ans, vector<bool> &used, vector< list<int> > &graph, int v)
{
	used[v] = true;
	color[v] = 1;
	for(auto i: graph[v])
	{
		if (color[i] == 1)
			cycleExists = true;

		if (!used[i])
			dfs(color, ans, used, graph, i);
	}
	color[v] = 2;
	ans.push_back(v);
}

int main()
{
	int N,M = 0;
	cin >> N >> M;
	vector< list<int> > graph(N + 1);
	list<int> ans;

	int v1, v2 = 0;
	for (int i = 0; i < M; i++)
	{
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
	}

	vector<bool> used(N + 1, false);
	vector<int> color(N + 1, 0);
	for(int i = 1; i <= N; i++)
	{
		if (!used[i])
		{
			dfs(color, ans, used, graph, i);
		}
	}
	if (cycleExists)
	{
		cout << -1 << endl;
		return(0);
	}
	reverse(ans.begin(), ans.end());
	for (auto i: ans)
	{
		cout << i << " ";
	}
	cout << endl;
	return 0;
}

