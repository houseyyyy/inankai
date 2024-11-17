#include <iostream>
#include <cstring>
using namespace std;
int dijkstra(int n, int m, int** g)
{
	int* dist = new int[n];
	bool* is = new bool[n];
	memset(dist, 0x3f,sizeof(int)*n);
	memset(is, 0, sizeof(bool)*n);
	dist[0] = 0;
	for (int i = 0; i < n; i++)
	{
		int t = -1;
		for (int j = 0; j < n; j++)
		{
			if (!is[j] && (t == -1 || dist[t] > dist[j]))
				t = j;
		}
		for (int j = 0; j < n; j++)
		{
			dist[j] = min(dist[j], dist[t] + g[t][j]);
		}
		is[t] = true;
	}

	if (dist[n - 1] == 0x3f3f3f3f)return -1;
	return dist[n - 1];
}
int main()
{
	int n, m;
	cin >> n >> m;
	int** g = new int* [n];
	for (int i = 0; i < n; i++)
		g[i] = new int[n], memset(g[i], 0x3f, sizeof(int)* n);

	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		g[a - 1][b - 1] = min(g[a - 1][b - 1], c);
	}
	int t = dijkstra(n, m, g);
	cout << t;
	return 0;
}