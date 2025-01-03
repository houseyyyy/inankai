#include <bits/stdc++.h>

int main()
{
	int n;
	std::cin>> n;
	int* a = new int[n];
	for(int i = 0; i < n;i++)std::cin>> a[i];
	int j = 0;
	int ans = 0;
	while(j != n - 1)
	{
		std::sort(a + j,a + n);
		a[j + 1] += a[j];
		ans += a[j + 1];
		j ++;
	}
	std::cout<< ans;
	return 0;
}