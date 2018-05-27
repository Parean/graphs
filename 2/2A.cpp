
#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>

using namespace std;
void bfs(vector<int> &dist, vector<bool> &used, vector< list<int> > &graph, int v)
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
				dist[i] = dist[current] + 1;
			}
		}

	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N,begin,end = 0;
	cin >> N >> begin >> end ;
	vector< list<int> > graph(N + 1);

	int v = 0;
	for (int i = 1; i <= N; i++)
	{
		for(int j = 1; j <= N; j++)
		{
			cin >> v;
			if (v)
				graph[i].push_back(j);
		}
	}


	vector<bool> used(N + 1, false);
	vector<int> dist(N + 1, 0);
	bfs(dist, used, graph, begin);
	cout << dist[end] << '\n';
	return 0;
}

