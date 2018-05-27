
#include <cstdio>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

void dfs(vector<bool> &used, vector< list<int> > &graph, int v)
{
	used[v] = true;
	for(auto i: graph[v])
	{
		if (!used[i])
			dfs(used, graph, i);
	}
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
		graph[v2].push_back(v1);
	}

	vector<bool> used(N + 1, false);
	int numOfComp = 0;
	for(int i = 1; i <= N; i++)
	{
		if (!used[i])
		{
			dfs(used, graph, i);
			numOfComp++;
		}
	}

	if (numOfComp > 1)
		cout << "NO" << endl;
	else
		cout << "YES" << endl;

	return 0;
}

