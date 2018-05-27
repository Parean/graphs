
#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>

using namespace std;

void bfs(vector <vector<int> > &dist, vector<bool> &used, vector< list<int> > &graph, int v)
{
	queue<int> q;
	q.push(v);
	used[v] = true;

	while(!q.empty())
	{
		int current = q.front();
		q.pop();

		for(auto i: graph[current])
		{
			if(!used[i])
			{
				used[i] = true;
				q.push(i);
				dist[v][i] = dist[v][current] + 1;
			}
		}

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

	vector<bool> used(N + 1);
	vector<vector <int> > dist(N + 1, vector<int>(N + 1, 0));

	for(int i = 1; i <= N; i++)
	{
		used.clear();
		used.insert(used.begin(), N + 1, false);
		bfs(dist, used, graph, i);
	}

	int s = 0;
	for(int i = 1; i <= N; i++)
	{
		for(int j = i; j <= N; j++)
		{
			// cout << dist[i][j] << ' ';
			s += dist[i][j];
		}
		// cout << endl;
	}

	cout << s << endl;
	return 0;
}

