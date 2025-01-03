#include <iostream>
#include <algorithm>
using namespace std;

struct node
{
	int x,y,z;
};
bool cmp(node &a,node & b)
{
	return a. z < b.z;
}
int find(int i,int * &p)
{
	if(p[i] != i)p[i] = find(p[i],p);
	else return i;
}
int kruskal(node* edg,int* &p,int n,int m)
{
	int ans = 0;
	int count = 0;
	for(int i = 1; i <= m;i++)
	{
		if(count == n - 1)break;
		int pa = find(edg[i].x,p);
		int pb = find(edg[i].y,p);
		if(pa != pb)
		{
			ans += edg[i].z;
			p[pb] = pa;
			count ++;
		}
	}
	if(count == n - 1)return ans;
	else return 0x3f3f3f3f;
}
int main()
{	
	int n,m;
	cin>> n>> m;
	int* p = new int[n + 1];
	node* edg = new node[m + 1];
	for(int i = 0; i <= n;i++)p[i] = i;

	for(int i = 1; i <= m;i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		edg[i].x = a,edg[i].y = b,edg[i].z = c;
	}
	sort(edg + 1,edg + m + 1,cmp);
	int ans = kruskal(edg,p,n,m);
	if(ans == 0x3f3f3f3f)cout<< "impossible";
	else cout<< ans;
	return 0;
}