
#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>

using namespace std;
int maxDist;
int maxI;
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
				if(dist[i] > maxDist)
					maxI = i;
			}
		}

	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int N,M,benz = 0;
	cin >> N >> benz;
	M = N-1;
	vector< list<int> > graph(N + 1);

	int v1, v2 = 0;
	for (int i = 0; i < M; i++)
	{
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}

	vector<bool> used(N + 1, false);
	vector<bool> used1(N + 1, false);
	vector<int> dist(N + 1, 0);
	vector<int> dist1(N + 1, 0);
	bfs(dist, used, graph, 1);

	bfs(dist1, used1, graph, maxI);
	int maxPath = dist1[maxI];
	int r = benz - maxPath;
	if(r < 0)
	{
		cout << benz + 1 << '\n';
	}
	else
	{
		cout << min(r / 2, N - maxPath - 1) + maxPath + 1 << '\n';
	}
	return 0;
}

