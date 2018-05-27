

#include <iostream>
#include <vector>
#include <cfloat>
#include <math.h>
#include <iomanip>

using namespace std;


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N = 0;
	cin >> N;

	vector<pair<int,int>> coords(N);

	int x,y = 0;
	for (int i = 0; i < N; i++)
	{
		cin >> x >> y;
		coords[i].first = x;
		coords[i].second = y;
	}

	// for (int i = 0; i < N; i++)
	// {
	// 	for (int j = 0; j < N; j++)
	// 	{
	// 		cout << graph[i][j] << ' ';
	// 	}
	// 	cout << endl;
	// }
	//
	double s = 0;
	vector<bool> used(N,false);
	vector<double> minE(N, DBL_MAX);
	vector<int> endE (N, 0);
	minE[0] = 0;

	for(int i = 0; i < N; i++)
	{
		int vMin = -1;
		for(int j = 0; j < N; j++)
		{
			if(!used[j] && (vMin == -1 || minE[j] < minE[vMin]))
				vMin = j;
		}
		s += sqrt(pow(coords[vMin].first - coords[endE[vMin]].first, 2) + pow(coords[vMin].second - coords[endE[vMin]].second, 2));

		used[vMin] = true;

		for(int to = 0; to < N; to++)
		{
            double a = sqrt(pow(coords[vMin].first - coords[to].first, 2) + pow(coords[vMin].second - coords[to].second, 2));
			if(a < minE[to])
			{
				minE[to] = a;
				endE[to] = vMin;
			}
		}
	}

	cout << setprecision(17) << s << '\n';

	return 0;
}
