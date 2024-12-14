#include <bits/stdc++.h>

using namespace std;
int n,m,y;
int** g;
int* f;
void dijkstra(int*& dist,bool*& is,int** g)
{
	int flag = 1;
	dist[y - 1] = 0;
	for(int k = 0;k < n;k++)
	{
		int t = -1;
		for(int i = 0; i < n;i++)
		{
			if(!is[i] && (t == -1 || dist[i] < dist[t]))
			t = i;
		}
		for(int j = 0; j < n;j++)
		{
			dist[j] = min(dist[j],dist[t] + g[t][j]);
			if(dist[j] == dist[t] + g[t][j])f[j] = t;
		}
		is[t] = true;
		if(dist[t] != 0x3f3f3f3f && t != y - 1)
		{
			cout<< "No." << flag ++ <<" : ";
			vector<int> ans;
			int temp = t;
			while(true)
			{
				if(temp == y - 1)
				{
					ans.push_back(temp);
					break;
				}
				ans.push_back(temp);
				temp = f[temp];
			}
			for(int i = ans.size() - 1;i >= 0;i--)
			{
				cout<<ans[i] + 1<< ' ';
				if(i != 0)cout<<"-> ";
			}
			cout<<", d = " << dist[t] << endl;
		}
	}
	if(flag == n)return;
	vector<int> ans;
	cout<<"No."<< flag <<" : No Path to ";
	for(int i = 0;i < n;i++)
	{
		if(dist[i] == 0x3f3f3f3f)
		{
			ans.push_back(i + 1);
		}
	}
	for(int i = 0;i < ans.size();i++)cout<<ans[i] <<" \n"[i + 1 == ans.size()];
	
}
int main()
{
	cin>> n >> m;
	bool* is = new bool[n];
	for(int i = 0; i < n;i++)is[i] = false;
	f = new int[n];
	int* dist = new int[n];
	memset(dist,0x3f,sizeof(int)* n);

	g = new int*[n];
	for(int i = 0;i < n;i++)
	{
		g[i] = new int[n];
		memset(g[i],0x3f,sizeof(int) * n);
	}
	for(int i = 0;i < m;i++)
	{
		int a,b,c;
		cin>> a >> b >> c;
		g[a - 1][b - 1] = min(g[a - 1][b - 1],c);
	}
	cin>> y;
	for(int i = 0;i < n;i++)f[i] = y - 1;
	dijkstra(dist,is,g);
	return 0;
}