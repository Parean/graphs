
#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;
bool cycleExists = false;

void dfs(list<int> &ans, vector<bool> &used, vector< list<int> > &graphOut, int v)
{
	used[v] = true;
	for(auto i: graphOut[v])
	{
		if (!used[i])
			dfs(ans, used, graphOut, i);
	}
	ans.push_back(v);
}

int main()
{
	int N,M = 0;
	cin >> N >> M;
	vector< list<int> > graphOut(N + 1);
	vector< list<int> > graphIn(N + 1);
	vector<int> lengths(N + 1);
	list<int> ans;

	int v1, v2 = 0;
	for (int i = 0; i < M; i++)
	{
		cin >> v1 >> v2;
		graphOut[v1].push_back(v2);
		graphIn[v2].push_back(v1);
	}

	vector<bool> used(N + 1, false);
	for(int i = 1; i <= N; i++)
	{
		if (!used[i])
		{
			dfs(ans, used, graphOut, i);
		}
	}
	reverse(ans.begin(), ans.end());
	for (auto i: ans)
	{
		if (graphIn[i].size() == 0)
		{
			lengths[i] = 0;
			continue;
		}

		int max = 0;
		for (auto v: graphIn[i])
		{
			if (max < lengths[v])
				max = lengths[v];
		}
		lengths[i] = 1 + max;
	}

	cout << *max_element(lengths.begin(), lengths.end()) << endl;
	return 0;
}

