

#include <iostream>
#include <vector>
#include <list>
#include <limits.h>
#include <algorithm>
#include <set>
#include <unordered_map>

using namespace std;

typedef long long ll;
int const N = 100100;
int block_size = 0;

vector<char> used(N,0);
vector<int> lca_first(N);
vector<int> lca_order(2*N);
vector<int> lca_h(N);
vector<vector<int>> graph(N);
vector<int> type(2*N,0);
vector<vector<int>> table(2*N, vector<int>(20,-1));
vector< vector< vector<int> > > block_min(2048, vector< vector<int> >(10, vector<int>(10,-1)));
vector<int> logs(2*N);
int first_index = -1;

void lca_dfs (int v,int h = 1)
{
	used[v] = true;
	lca_h[v] = h;
	lca_order[++first_index] = v;
	lca_first[v] = first_index;
	for (auto u : graph[v])
	{
		if (used[u])
			continue;

		lca_dfs (u,h+1);
		lca_order[++first_index] = v;
	}
}

int block_RMQ(int block_number, int l, int r)
{
	return block_min[type[block_number]][l][r] + block_number * block_size;
}

int my_min(int a, int b)
{
	if (lca_h[a] < lca_h[b])
		return a;
	else
		return b;
}

int RMQ(int l, int r)
{
	auto bl = l / block_size;
	auto br = r / block_size;

	if (bl == br)
		return lca_order[block_min[type[bl]][l % block_size][r % block_size] + bl * block_size];

	if (bl + 1 < br)
	{
		int ansb = my_min(
			lca_order[ table[bl + 1][logs[br - bl - 1]] ],
			lca_order[ table[br - (1 << logs[br - bl - 1])][logs[br - bl - 1]] ]
		);

		int ansl = lca_order[block_min[type[bl]][l % block_size][block_size - 1] + bl * block_size];
		int ansr = lca_order[block_min[type[br]][0][r % block_size] + br * block_size];

		return my_min(ansb, my_min(ansl, ansr));
	}

	int ansl = lca_order[block_min[type[bl]][l % block_size][block_size - 1] + bl * block_size];
	int ansr = lca_order[block_min[type[br]][0][r % block_size] + br * block_size];

	return my_min(ansl, ansr);
}

int RMQ_opt(int l, int r)
{
	auto bl = l / block_size;
	auto br = r / block_size;

	if (bl == br)
		return lca_order[block_min[type[bl]][l % block_size][r % block_size] + bl * block_size];

	if (bl + 1 < br)
	{
		int ansb = 0;
		if (lca_h[ lca_order[ table[bl + 1][logs[br - bl - 1]] ] ] <
			lca_h[ lca_order[ table[br - (1 << logs[br - bl - 1])][logs[br - bl - 1]] ] ]
		)
			ansb = lca_order[ table[bl + 1][logs[br - bl - 1]] ];
		else
			ansb = lca_order[ table[br - (1 << logs[br - bl - 1])][logs[br - bl - 1]] ];

		int ansl = lca_order[block_min[type[bl]][l % block_size][block_size - 1] + bl * block_size];
		int ansr = lca_order[block_min[type[br]][0][r % block_size] + br * block_size];

		if (lca_h[ansl] < lca_h[ansr])
			if (lca_h[ansl] < lca_h[ansb])
				return ansl;
			else
				return ansb;
		else
			if (lca_h[ansr] < lca_h[ansb])
				return ansr;
			else
				return ansb;
	}

	int ansl = lca_order[block_min[type[bl]][l % block_size][block_size - 1] + bl * block_size];
	int ansr = lca_order[block_min[type[br]][0][r % block_size] + br * block_size];

	if (lca_h[ansl] < lca_h[ansr])
		return ansl;
	else
		return ansr;
}

int main()
{
	//freopen("in", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n,m = 0;
	cin >> n >> m;
	int new_size = 2 * n - 1;
	int node;
	for(int i = 1; i < n; i++)
	{
		cin >> node;
		graph[node].push_back(i);
		graph[i].push_back(node);
	}

	ll x,y,z,a1,a2 = 0;
	cin >> a1 >> a2 >> x >> y >> z;

	lca_dfs(0);

	block_size = max(ceil(log2(new_size) / 2), 1.0);
	int num_of_blocks = ceil(new_size / (float)block_size);
	int k = ceil(log2(num_of_blocks)) + 1;

	int min = -1;
	int current_block = 0;
	int j = 0;
	int i = 0;
	for (; i < new_size; i++)
	{
		int v = lca_order[i];

		if (j == block_size)
		{
			j = 0;
			current_block++;
			table[current_block - 1][0] = min;
			min = -1;
		}

		if (min == -1 || lca_h[lca_order[min]] > lca_h[v])
			min = i;

		if (j && (lca_h[lca_order[i - 1]] < lca_h[lca_order[i]]))
			type[current_block] += (1 << (j - 1));

		j++;
	}

	table[current_block][0] = min;

	while(j < block_size)
	{
		type[current_block] += (1 << (j - 1));
		j++;
	}

	for (int j = 1; j < k; j++)
	{
		int ind = 0;
		int i = 0;
		for(; (ind = i + (1 << (j-1))) < num_of_blocks; i++)
		{
			if (lca_h[lca_order[table[i][j-1]]] < lca_h[lca_order[table[ind][j-1]]])
				table[i][j] = table[i][j-1];
			else
				table[i][j] = table[ind][j-1];
		}

		for(; i < num_of_blocks; i++)
			table[i][j] = table[i][j-1];
	}

	i = 0;
	for(; i < num_of_blocks; i++)
	{
		logs[i] = log2(i);
		auto t = type[i];
		if (block_min[t][0][0] != -1)
			continue;

			for (int l = 0; l < block_size; l++)
		{
			block_min[t][l][l] = l;
			for (int r = l + 1; r < block_size; r++)
			{
				block_min[t][l][r] = block_min[t][l][r - 1];
				if (
					i * block_size + r <= new_size &&
					lca_h[lca_order[i * block_size + block_min[t][l][r]]] > lca_h[lca_order[i * block_size + r]]
				)
					block_min[t][l][r] = r;
			}
		}
	}
	logs[i] = log2(i);

	int l = lca_first[a1];
	int r = lca_first[a2];
	if (r < l)
		swap(l,r);

	ll v = RMQ(l,r);
	ll s = v;
	for (int i = 2; i < m + 1; i++)
	{
		a1 = (x * a1 + y * a2 + z) % n;
		a2 = (x * a2 + y * a1 + z) % n;

		l = lca_first[(a1 + v) % n];
		r = lca_first[a2];

		if (r < l)
			swap(l,r);

		v = RMQ(l,r);
		s += v;
	}

	cout << s << endl;
}
