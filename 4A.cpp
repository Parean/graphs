
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 300;
vector<int> graph[MAXN];
vector<bool> used(MAXN, false);
vector<int> mt(MAXN, -1);

bool kuhn(int v)
{
	if (used[v])
		return false;

	used[v] = true;

	for (int i = 0; i < graph[v].size(); i++)
	{
		int end = graph[v][i];

		if (mt[end] == -1 || kuhn(mt[end]))
		{
			mt[end] = v;
			return true;
		}
	}

	return false;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int A, B;
	cin >> A >> B;
	int end, i = 0;

	while (i < A)
	{
		cin >> end;
		if (end != 0)
		{
			graph[i].push_back(end - 1);
		}
		else
			i++;
	}

	for (int v = 0; v < A; v++)
	{
		fill(used.begin(), used.end(), false);
		kuhn(v);
	}

	int n = 0;

	vector<pair<int, int> > result;

	for (int i = 0; i < B; i++)
		if (mt[i] != -1)
		{
			n++;
			result.push_back({ mt[i], i });
		}

	cout << n << endl;

	for (int i = 0; i < result.size(); i++)
	{
		cout << result[i].first + 1 << " " << result[i].second + 1 << endl;
	}

	return 0;
}

