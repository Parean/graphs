
#include <iostream>
#include <vector>
#include <list>
#include <limits.h>
#include <algorithm>
#include <set>
#include <utility>


using namespace std;

vector<char> used;
vector<int> color;
vector<int> order;

void dfs(
	vector< vector<int> > &graph,
	int v
)
{
	used[v] = true;
	for(auto u: graph[v])
	{
		if (!used[u])
			dfs(graph, u);
	}
	order.push_back(v);
}

void dfs2(
	vector< vector<int> > &graph,
	int v,
	int c
)
{
	color[v] = c;
	for(auto u: graph[v])
	{
		if (color[u] == -1)
			dfs2(graph, u, c);
	}
}

int main()
{
	//freopen("in", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N,M;
	cin >> N >> M;
	vector<vector <int> > graph(N + 1);
	vector<vector <int> > graphT(N + 1);

	int v1, v2 = 0;
	for (int i = 0; i < M; i++)
	{
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		graphT[v2].push_back(v1);
	}

	used.assign(N + 1, false);
	for(int i = 1; i <= N; i++)
	{
		if(!used[i])
			dfs(graph,i);
	}

	color.assign(N + 1, -1);
	int c = 0;
	for(auto i = order.rbegin(); i != order.rend(); ++i)
	{
		if(color[*i] == -1)
		{
			dfs2(graphT,*i,c++);
		}
	}

	set<pair<int,int>> s;
	for (int i = 1; i <= N; i++)
	{
		for(auto v : graph[i])
		{
			if(color[i] != color[v])
				s.insert(make_pair(color[i],color[v]));
		}
	}

	cout << s.size() << '\n';
	return 0;
}

