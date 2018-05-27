
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 100000;
vector<int> graph[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N, M;
	cin >> N >> M;
	int begin, end;

	for (int i = 0; i < M; i++)
	{
		cin >> begin >> end;
		graph[begin - 1].push_back(end - 1);
		graph[end - 1].push_back(begin - 1);
	}

	vector<int> color(N, -1);
	bool isPossible = true;

	queue<int> q;
	for (int k = 0; k < N && isPossible; k++)
	{
		if (color[k] == -1)
		{
			q.push(k);
			color[k] = 0;

			while (!q.empty() && isPossible)
			{
				int curent = q.front();
				q.pop();

				for (int i = 0; i < graph[curent].size(); i++)
				{
					if (color[curent] == color[graph[curent][i]])
					{
						isPossible = false;
					}

					else if (color[graph[curent][i]] == -1)
					{
						color[graph[curent][i]] = 1 - color[curent];
						q.push(graph[curent][i]);
					}
				}
			}
		}
	}

	if (!isPossible)
		cout << "NO" << endl;
	else
	{
		cout << "YES" << endl;
		for (int i = 0; i < N; i++)
		{
			cout << color[i] + 1 << " ";
		}
	}

	return 0;
}

