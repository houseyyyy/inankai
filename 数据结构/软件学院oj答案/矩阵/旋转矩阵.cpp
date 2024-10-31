#include <bits/stdc++.h>

int main()
{
	int n,m;
	std::cin>> n >> m;
	int** A = new int*[n];
	for(int i = 0; i < n;i++)
	{
		A[i] = new int[m];
		for(int j = 0; j < m;j++)std::cin>> A[i][j];
	}
	int k = 0,i = 0,j = 0,times = 0;
	int t = ceil(std::min(n,m) / 2.0);

	while(t--)
	{
		if(k % 2 == 0)
		{
			while(j < m - k)
			{
				std::cout<< A[i][j++] << ' ';times ++;if(times == n*m)return 0;
			}
			j--;i++;
			while(i < n - k)
			{
				std::cout<< A[i++][j] << ' ';times ++;if(times == n*m)return 0;
			}
			j--;i--;
			while(j >= k)
			{
				std::cout<< A[i][j--] << ' ';times ++;if(times == n*m)return 0;
			}
			j++;i--;
			while(i >= k + 1)
			{	
				std::cout<< A[i--][j] << ' ';times ++;if(times == n*m)return 0;
			}
			j++;i++;
		}
		else 
		{
			while(i < n - k)
			{
				std::cout<< A[i++][j]<< ' ';times ++;if(times == n*m)return 0;
			}
			i--;j++;
			while(j < m - k)
			{
				std::cout<< A[i][j++] << ' ';times ++;if(times == n*m)return 0;
			}
			j--;i--;
			while(i >= k)
			{
				std::cout<< A[i--][j] << ' ';times ++;if(times == n*m)return 0;
			}
			i++;j--;
			while(j >= k + 1)
			{
				std::cout<< A[i][j--] <<' ';times ++;if(times == n*m)return 0;
			}
			j++;i++;
		}
		k++;

	}
	return 0;
}