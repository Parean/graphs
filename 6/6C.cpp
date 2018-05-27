#include<vector>
#include<iostream>
#include<algorithm>

typedef long long ll;

using namespace std;

const int N=(int)1e5;
const int M=(int)1e5;

vector<int> nextt;
vector<int> cost;
vector<int> flow;
vector<int> to;
vector<int> head(N, -1);
vector<bool> used(N, false);

bool dfs(int v,int h)
{
	if(v==h)
		return true;

	if(used[v])
		return false;

	used[v] = true;
	for(int e = head[v]; e != -1; e = nextt[e])
	{
		if(cost[e] > flow[e] && dfs(to[e],h))
		{
			flow[e]++;
			flow[e^1]--;
			return true;
		}
	}
	return false;
}

int main()
{
	freopen("in", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m,a,h;
	cin >> n >> m >> a >> h;
	a--,h--;

	int x,y;
	int e = 0;
	for(int i = 0; i < m; i++)
	{
		cin >> x >> y;
		x--,y--;

		nextt.push_back(head[x]);
		head[x] = e++;
		to.push_back(y);
		cost.push_back(1);
		flow.push_back(0);

		nextt.push_back(head[y]);
		head[y] = e++;
		to.push_back(x);
		cost.push_back(0);
		flow.push_back(0);
	}

	for(int i = 0; i < 2; i++)
	{
		used.assign(N,false);
		if(!dfs(a,h))
		{
			cout << "NO" << endl;
			return 0;
		}
	}

	cout << "YES" << endl;

	for(int i = 0; i < 2; i++)
	{
		int current = a;
		cout << current + 1;
		while(current != h)
		{
			for(int e = head[current]; e != -1; e = nextt[e])
			{
				if(flow[e] > 0)
				{
					flow[e]--;
					flow[e^1]++;
					current = to[e];
					break;
				}
			}
			cout << " " << current + 1;
		}
		cout << endl;
	}

	return 0;
}
