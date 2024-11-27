#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int* a = new int[n];
	for(int i = 0; i < n;i++)cin>> a[i];
	int ans = 0;
	for(int i = 0;i < n - 1;i++)
	{
		sort(a + i,a + n);
		a[i + 1] = a[i] + a[i + 1];
		ans += a[i + 1];
	}
	cout<< ans;
	return 0;
}