
#include <iostream>
#include <vector>
#include <list>
#include <limits.h>
#include <algorithm>

using namespace std;

bool floid(vector<vector <long long> > &graph)
{
	auto N = graph.size() - 1;
	for (int k=1; k<=N; ++k)
	{
		for (int i=1; i<=N; ++i)
		{
			for (int j=1; j<=N; ++j)
			{
				if (graph[i][k] < LONG_LONG_MAX && graph[k][j] < LONG_LONG_MAX)
					graph[i][j] = min(graph[i][j], max(-LONG_LONG_MAX, graph[i][k] + graph[k][j]));
			}
		}
	}

	for (int i = 1; i <= N; i++)
	{
		if (graph[i][i] < 0)
			return true;
	}

	return false;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N = 0;
	cin >> N;
	vector<vector <long long> > graph(N + 1, vector<long long>(N + 1));

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			int k = 0;
			cin >> k;
			if(k == 100000)
				graph[i][j] = LONG_LONG_MAX;
			else
				graph[i][j] = k;
		}
	}

	if(floid(graph))
		cout << "YES\n";
	else
		cout << "NO\n";
	return 0;
}

