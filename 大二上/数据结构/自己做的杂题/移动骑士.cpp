#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
int dx[] = {-1,1};
int dy[] = {-2,2};

int n;
int sx,sy,ex,ey;
int nowceng;
bool isok(int x,int y)
{
	if(x < 0 || y < 0 || x >= n || y >= n)return false;
	else return true;
}
void bfs(int x,int y)
{	
	bool a[310][310];
	memset(a,0,sizeof(bool)* 310 * 310);
	int ans = 0;
	queue<pair<int,int> > q;
	q.push(pair<int,int> (x,y));
	a[x][y] = true;
	//temp record node number in this layer to pop
	int temp = 0;
	int co = 0;
	while(!q.empty())
	{
	    
		pair<int,int> k = q.front();
		q.pop();
		if(k.first == ex && k.second == ey)
		{
			cout << nowceng << endl;
			return;
		}
		for(int i = 0; i < 2;i++)
		{
			for(int j = 0;j < 2;j++)
			{
				if(isok(k.first + dx[i],k.second + dy[j]) && !a[k.first + dx[i]][k.second + dy[j]])
				{
					q.push(pair<int,int> (k.first + dx[i],k.second + dy[j]));
					co++;
					a[k.first + dx[i]][k.second + dy[j]] = true;
				}
				if(isok(k.first + dy[i],k.second + dx[j]) && !a[k.first + dy[i]][k.second + dx[j]])
				{
					q.push(pair<int,int> (k.first + dy[i],k.second + dx[j]));
					co++;
					a[k.first + dy[i]][k.second + dx[j]] = true;
				}
			}
		}
		if(!temp)
		{
		    nowceng++;//temp = 0,current layer have been solved,go to next layer
		    temp = co;//record node number
		    co = 0;
		}
        temp --;//pop node so temp --;
	}
}
void solve()
{
	cin>> n >>sx >> sy >> ex >> ey;
	nowceng = 0;
	bfs(sx,sy);
}
int main()
{	
	int T;
	cin>> T;
	while(T--)
	{
		solve();
	}
	return 0;
}