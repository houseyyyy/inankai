#include <bits/stdc++.h>

int main()
{
	int n;
	std::cin>> n;
	int** a = new int* [n];
	int *b = new int[n];
	int *c = new int[n];
	int nb = 0,nc = 0,x,y;
	for(int i = 0;i < n;i++)
	{
		a[i] = new int[n];
		b[i] = 0;
		for(int j = 0;j < n;j++)
		std::cin>> a[i][j],b[i] += a[i][j];
		if(b[i] % 2 == 1)nb++,x = i;
	}
	for(int i = 0; i < n;i++)
	{
		c[i] = 0;
		for(int j = 0; j < n;j++)c[i] += a[j][i];
		if(c[i] % 2 == 1)nc++,y = i;
	}
	if(!nb && !nc)std::cout<<"OK";
	else if(nb == 1 && nc == 1)std::cout<<"Change bit (" << ++x <<"," << ++y << ")";
	else std::cout<< "Corrupt";
	return 0;
}