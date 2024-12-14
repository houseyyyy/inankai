#include <bits/stdc++.h>

using namespace std;
int n,m;
int main()
{
	cin>> n;
	int *a = new int[n];
	for(int i = 0;i < n;i++)cin>> a[i];
	for(int k = 1;k <= n;k++)
	{
		for(int i = 0;i + k < n;i ++)
		{
			if(a[i] > a[i + k])break;
			if(i + k >= n - 1)
			{
				cout<< k;
				return 0;
			}
		}
	}
	return 0;
}