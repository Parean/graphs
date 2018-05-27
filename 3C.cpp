
#include <limits.h>
#include <iostream>
#include <vector>
#include <cfloat>
#include <math.h>
#include <iomanip>
#include <utility>
#include <string>

using namespace std;

#define MAX 150010
int mas[3][MAX], dsuArray[MAX], res[MAX];
int Repr(int n)
{
  if (n == dsuArray[n]) return n;
  return dsuArray[n] = Repr(dsuArray[n]);
}

int Union(int x, int y)
{
  int x1 = Repr(x),y1 = Repr(y);
  dsuArray[x1] = y1;
  return (x1 == y1);
}

int main()
{
	// freopen("in", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	long N,M,k = 0;
	cin >> N >> M >> k;

	int v = 0;
	for (int i = 0; i < M; i++)
	{
		cin >> v >> v;
	}

	string op;
	for(int i = 0; i < k; i++)
	{
		cin >> op >> mas[1][i] >> mas[2][i];
		if (op[0] == 'a')
			mas[0][i] = 1;
		else
			mas[0][i] = 0;
	}

	for(int i = 1; i <= N; i++)
		dsuArray[i] = i;

	for(int i = k - 1; i >= 0; i--)
	{
		if (mas[0][i])
			res[i] = (Repr(mas[1][i]) == Repr(mas[2][i]));
		else
			Union(mas[1][i],mas[2][i]);
	}

	for(int i = 0; i < k; i++)
		if (mas[0][i])
			if (res[i])
				cout << "YES\n";
			else
				cout << "NO\n";

	return 0;
}

