
#include <iostream>
#include <vector>
#include <list>
#include <limits.h>
#include <algorithm>
#include <set>
#include <utility>

#define MAX 1010

using namespace std;

int graph[MAX][MAX], g[MAX][MAX];
vector<int> used;
int N = 0;
int numVisited = 0;

void dfs(int v, int type)
{
	numVisited++;
	used[v] = true;
	for(int i = 0; i < N; i++)
	{
		if (!used[i] && (type ? g[i][v] : g[v][i]))
			dfs(i,type);
	}
}

bool isAllVisited()
{
	return numVisited == used.size();
}

int main()
{
	//freopen("in", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			cin >> graph[i][j];
		}
	}

	long long L = 0;
	long long R = 10e9;

	while(L < R)
	{
		long long Mid = (L + R) / 2;
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				g[i][j] = (graph[i][j] <= Mid);

		numVisited = 0;
		used.assign(N, false);
		dfs(0,0);
		bool allVisited = 0;

		if (allVisited = isAllVisited())
		{
			numVisited = 0;
			used.assign(N, false);
			dfs(0,1);
			allVisited = isAllVisited();
		}

		if (allVisited)
			R = Mid;
		else
			L = Mid + 1;
	}

	cout << L << '\n';
}

