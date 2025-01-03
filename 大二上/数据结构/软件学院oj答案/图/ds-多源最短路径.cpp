#include <bits/stdc++.h>

using namespace std;
int n,m;
int g[30][30][30];
int main()
{
	cin>> n>> m;
	for(int k = 0;k <= n;k++)
	{
		for(int i = 1;i <= n;i++)
		{
			for(int j = 1;j <= n;j++)
			{
				if(i != j)g[i][j][k] = 0x3f3f3f3f;
				else g[i][j][k] = 0;
			}
		}
	}

	while(m --)
	{
		int x,y,z;
		cin>> x >> y >> z;
		g[x + 1][y + 1][0] = min(g[x + 1][y + 1][0],z);
	}

	for(int k = 1;k <=n;k++)
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= n;j++)
				g[i][j][k] = min(g[i][j][k - 1],g[i][k][k - 1] + g[k][j][k - 1]);
	for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j <= n;j++)
		{
			if(g[i][j][n] == 0x3f3f3f3f)cout<< -1;
			else cout<<g[i][j][n];
			cout<<" \n"[j == n];
		}
	}
	return 0;
}