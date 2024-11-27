#include <iostream>

using namespace std;
const int N = 1010;
int n,m;
int p[N];
int find(int i)
{
	if(p[i] != i)
	{
		p[i] = find(p[i]);
		return p[i];
	}
	else return i;
}
int main()
{
	cin >> n >> m;
	int cnt = n;
	for(int i = 1; i <= n;i++)p[i] = i;
	while(m --)
	{
		int x,y;
		cin >> x >> y;
		if(find(x) != find(y))
		{
			p[find(x)] = find(y);
			cnt --;
		}
	}
	cout<< cnt - 1;
	return 0;
}