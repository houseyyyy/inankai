#include <bits/stdc++.h>

const int dx[] = {-1,0,1,0};
const int dy[] = {0,-1,0,1};

bool isfind = 0;

void DFS(std::vector<std::vector<int> > matrix,int n,int m,int x,int y)
{	
	if(x == n - 1 && y == m - 1)
	{
		isfind = 1;
		return;
	}
	for(int i = 0;i < 4;i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(nx < 0 || nx == n || ny < 0 || ny == m)continue;
		if(matrix[nx][ny])
		{
			matrix[nx][ny] = 0;
			DFS(matrix,n,m,nx,ny);
			matrix[nx][ny] = 1;
		}
	}
}
int main()
{
	int n,m;
	std::cin>> n >> m;
	std::vector<std::vector<int> > vis(n,std::vector(m,1));
	char c;
	for(int i = 0; i < n;i++)
	{
		for(int j = 0; j < m;j++)
		{
			std::cin >> c;
			if(c == '#')vis[i][j] = 0;
		}
	}

	DFS(vis,n,m,0,0);
	if(isfind)std::cout<<"Yes";
	else std::cout<<"No";

	return 0;
}