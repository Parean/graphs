
#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

const int WALL   = -1;
const int BLANK  = -2;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

bool lee(int x1, int y1, int x2, int y2, vector<vector <int> > &grid, int H, int W)
{
	int wave;
	bool stop;

	wave = 0;
	grid[y1][x1] = 0;
	list< list <pair<int,int> > > waves;
	list<pair <int, int>> l;
	waves.push_front(l);

	waves.back().push_back(pair<int,int>(x1,y1));

	do
	{
		stop = true;
		list<pair <int, int>> l;
		waves.push_front(l);
		for(auto p: waves.back())
		{
			auto x = p.first;
			auto y = p.second;

			for (int k = 0; k < 4; ++k )
			{
				int iy = y + dy[k];
				int ix = x + dx[k];

				if ( iy >= 1 && iy <= H && ix >= 1 && ix <= W &&
					grid[iy][ix] == BLANK )
				{
					stop = false;
					grid[iy][ix] = wave + 1;
					waves.front().push_back(pair<int,int>(ix,iy));
				}
			}
		}
		waves.pop_back();
		wave++;
	}
	while (!stop && grid[y2][x2] == BLANK);

	return (grid[y2][x2] != BLANK);
}

int main()
{
	int W,H,x1,y1,x2,y2 = 0;
	cin >> W >> H >> x1 >> y1 >> x2 >> y2;
	vector<vector <int> > grid(H + 1, vector<int>(W + 1));

	char v = 0;
	for (int i = 1; i <= H; i++)
	{
		for (int j = 1; j <= W; j++)
		{
			cin >> v;
			if(v == '.')
				grid[i][j] = BLANK;
			else
				grid[i][j] = WALL;
		}
	}
	if (lee(x1, y1, x2, y2, grid, H, W))
	{
		cout << "YES" << endl;
		int dist = grid[y2][x2];
		int parentsX[dist + 1];
		int parentsY[dist + 1];
		int x = x2;
		int y = y2;
		int d = dist;
		while (d > 0 )
		{
			parentsX[d] = x;
			parentsY[d] = y;
			d--;
			for (int k = 0; k < 4; ++k)
			{
				int iy = y + dy[k];
				int ix = x + dx[k];

				if (iy >= 1 && iy <= H && ix >= 1 && ix <= W &&
					grid[iy][ix] == d)
					{
						x = x + dx[k];
						y = y + dy[k];
						break;
					}
			}
		}
		parentsX[0] = x1;
		parentsY[0] = y1;
		for(int i = 0; i <= dist; i++)
		{
			cout << parentsX[i] << ' ' << parentsY[i] << '\t';
		}
		cout << endl;
	}
	else
	{
		cout << "NO" << endl;
	}

	// for(int i = 1; i <= H; i++)
	// {
	// 	for(int j = 1; j <= W; j++)
	// 	{
	// 		cout << grid[i][j] << ' ';
	// 	}
	// 	 cout << endl;
	// }

	return 0;
}

