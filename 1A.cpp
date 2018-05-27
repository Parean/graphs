
#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main()
{
	int N = 0;
	cin >> N;
	vector< list<int> > vs(N);

	int v = 0;
	for (int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			cin >> v;
			if (j >= i && v)
				vs[i].push_back(j);
		}
	}

	for (int i = 0; i < N; i++)
	{
		for(auto num : vs[i])
			cout << i + 1 << ' ' << num + 1 << endl;
	}

	return 0;
}

