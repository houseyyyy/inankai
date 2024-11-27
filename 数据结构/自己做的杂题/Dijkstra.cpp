#include <iostream>
#include <cstring>
#include <stack>
using namespace std;
/*


dijkstra

data meaning:
dist[i] 表示结点i距离距离起始节点s的距离，最开始为无穷
is[i] i的最短路径是否确定
g[i][j] i结点到 j结点 有距离为g[i][j]的路径，0x3f3f3f3f 表示不相邻

1.将起始结点的dist置为0，自己到自己的距离是0
2.寻找距离开始结点s 最近的并且没有确定最短路径的结点t，标志最短路径确定
3.更新所有结点到开始节点的距离，要么保持以前，要么经过结点t再到当前遍历到的结点



*/
int*fro;
int s,e;
int dijkstra(int n, int m, int** g)
{
	fro = new int[n];
	for(int i = 0;i < n;i++)fro[i] = i;

	int* dist = new int[n];
	bool* is = new bool[n];
	memset(dist, 0x3f,sizeof(int)*n);
	memset(is, 0, sizeof(bool)*n);
	dist[s - 1] = 0;
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
			if(dist[j] == dist[t] + g[t][j])
			{
				fro[j] = t;
			}
		}
		is[t] = true;
	}
	//输出路径
	stack<int> path;
	path.push(e);
	for(int i = e - 1;;i = fro[i])
	{
		if(fro[i] == i)break;
		path.push(fro[i] + 1);
	}
	while(!path.empty())
	{
		cout<<path.top();
		if(path.size() > 1)cout<<"->";
		path.pop();
	}
	cout<<endl;

	if (dist[e - 1] == 0x3f3f3f3f)return -1;
	return dist[e - 1];
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
		g[b - 1][a - 1] = g[a - 1][b - 1] = min(g[a - 1][b - 1], c);
	}
	cin>> s >> e;
	int t = dijkstra(n, m, g);
	cout << t;
	return 0;
}