#include <bits/stdc++.h>

long f(int n)
{

	long ans = 1;
	while(n)
	{
		ans *= n--;
	}
	return ans;
}
long C(int n,int k)
{
	return f(n)/f(k)/f(n-k);
}
int main()
{
	long a,b,n;
	std::cin>> a >> b >> n;
	for(int i = 0; i <= n;i++)
	{
		int k =  pow(a,n-i) * pow(b,i) * C(n,i);
		
		if(k == 1)
		{
			if(i != 0)
			{
				std::cout<<"+";
			}
		}
		else if(k == -1)
		{
			std::cout<< "-";
		}
		else if(k == 0)
		{
			continue;
		}
		else {
			if(k > 0 && i)std::cout<< "+";
			std::cout<< k;
		}
		if(n - i != 0)
		{
			if(n - i == 1)std::cout<< "x";
			else std::cout<< "x^" << n - i;
		}
		if(i != 0)
		{
			if(i == 1)std::cout<< "y";
			else std::cout<< "y^" << i;
		}
	}
	return 0;
}