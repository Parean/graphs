
#include <iostream>
#include <vector>

const int MAXN = 100001;
int bridges=0;
std::vector<int> par(MAXN,-1), bl(MAXN), comp(MAXN), size(MAXN,1);
using namespace std;

void init(int n) {
	for (int i=0; i<n; ++i) {
		bl[i] = comp[i] = i;
	}
}

int get (int v) {
	if (v==-1)
		return -1;

	return bl[v]==v ? v : bl[v]=get(bl[v]);
}

int get_comp (int v) {
	v = get(v);
	return comp[v]==v ? v : comp[v]=get_comp(comp[v]);
}

void make_root (int v) {
	v = get(v);
	int root = v,
		child = -1;
	while (v != -1) {
		int p = get(par[v]);
		par[v] = child;
		comp[v] = root;
		child=v;  v=p;
	}
	size[root] = size[child];
}

int cu, u[MAXN];

void merge_path (int a, int b) {
	++cu;

	vector<int> va, vb;
	int lca = -1;
	for(;;) {
		if (a != -1) {
			a = get(a);
			va.push_back (a);

			if (u[a] == cu) {
				lca = a;
				break;
			}
			u[a] = cu;

			a = par[a];
		}

		if (b != -1) {
			b = get(b);
			vb.push_back (b);

			if (u[b] == cu) {
				lca = b;
				break;
			}
			u[b] = cu;

			b = par[b];
		}
	}

	for (size_t i=0; i<va.size(); ++i) {
		bl[va[i]] = lca;
		if (va[i] == lca)  break;
		--bridges;
	}
	for (size_t i=0; i<vb.size(); ++i) {
		bl[vb[i]] = lca;
		if (vb[i] == lca)  break;
		--bridges;
	}
}

void add_edge (int a, int b) {
	a = get(a);   b = get(b);
	if (a == b)  return;

	int ca = get_comp(a),
		cb = get_comp(b);
	if (ca != cb) {
		++bridges;
		if (size[ca] > size[cb]) {
			swap (a, b);
			swap (ca, cb);
		}
		make_root (a);
		par[a] = comp[a] = b;
		size[cb] += size[a];
	}
	else
		merge_path (a, b);
}

int main()
{
	//freopen("in", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N,M,K;
	cin >> N >> M;
	int a,b = 0;

	init(N + 1);
	for(int i = 0; i < M; i++)
	{
		cin >> a >> b;
		add_edge(a,b);
	}

	cin >> K;
	for(int i = 0; i < K; i++)
	{
		cin >> a >> b;
		add_edge(a,b);
		cout << bridges << '\n';
	}

}

