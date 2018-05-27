#include <bits/stdc++.h>
#include <limits.h>

using namespace std;

const int N = 100;

struct Edge
{
	Edge(int to, int c, int ind, int rev):
		to(to),
		c(c),
		ind(ind),
		rev(rev)
		{}

	int to, c, ind, rev;
};

int DF, F, S, T, n, m, cc = 1, u[N];
vector<Edge> c[N];

int dfs( int v, int df = INT_MAX)
{
	if (v == T)
		return DF = df;

	u[v] = cc;
	for (auto &e : c[v])
	{
		if (e.c > 0 && u[e.to] != cc && dfs(e.to, min(df, e.c)))
		{
			e.c -= DF;
			c[e.to][e.rev].c += DF;
			return 1;
		}
	}
	return 0;
}

int main()
{
	freopen("in", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	int a, b, c;
	for (int i = 0; i < n; i++)
	{
		cin >> a >> b >> c;
		a--;
		b--;
		c[a].push_back(Edge(b, x, i, c[a].size()));
		c[b].push_back(Edge(a, x, i, c[b].size()));
	}

	S = 0, T = n - 1;
	while (dfs(S))
		cc++, F += DF;

	vector<int> ans;
	for (int i = 0; i < n; i++)
	{
		if (u[i] == cc)
		{
			for (auto e : c[i])
			{
				if (u[e.to] != cc)
					ans.push_back(e.ind);
			}
		}
	}

	cout << ans.size() << ' ' << F;
	sort(ans.begin(), ans.end());
	for (int x : ans)
		cout << x + 1 << ' ';
	return 0;
}
