#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
const int N = 10010;
int a[N],temp[N];
int n;
void output()
{
	for(int i = 0;i < n;i++)cout<< a[i] << " \n"[i + 1 == n];
}
void bubble_sort()
{
	for(int i = 0; i < n;i++)
	{
		for(int j = n - 1;j > i;j--)
		{
			if(a[j] < a[j - 1])swap(a[j],a[j - 1]);
		}
	}
}
void select_sort()
{
	for(int i = 0;i < n;i++)
	{
		int Min = a[i];
		for(int j = i;j < n;j++)
		{
			if(a[j] < Min)
			{
				//first change Min ,then swap
				Min = a[j];
				swap(a[i],a[j]);
			}
		}
	}
}
void insert_sort1()
{
	for(int i = 1;i < n;i++)
	{
		for(int j = i;j > 0;j --)
		{
			if(a[j] < a[j - 1])swap(a[j],a[j - 1]);
		}
	}
}
void insert_sort2()
{
	for(int i = 0;i + 1 < n;i++)
	{
		int x = a[i + 1];
		for(int j = 0;j <= i;j++)
		{
			if(x <= a[j])
			{
				for(int k = i + 1;k > j;k--)
				{
					a[k] = a[k - 1];
				}
				a[j] = x;
				break;
			}
		}
	}
}
void quick_sort(int l,int r)
{
	if(l >= r)return ;
	int mid = (l + r) / 2;
	int x = a[mid];
	int i = l - 1,j = r + 1;
	while(i < j)
	{
		do i++;while(a[i] < x);
		do j--;while(a[j] > x);
		if(i < j)swap(a[i],a[j]);
	}
	quick_sort(l,j);quick_sort(j + 1,r);
}
void merge_sort1(int l,int r)
{
	if(l >= r)return ;

	int mid = (l + r) / 2;

	merge_sort1(l,mid);merge_sort1(mid + 1,r);

	int k = 0,i = l, j = mid + 1;
	while(i <= mid && j <= r)
		if(a[i] < a[j])temp[k++] = a[i++];
		else temp[k++] = a[j++];
	while(i <= mid)temp[k++] = a[i++];
	while(j <= r)temp[k++] = a[j++];

	for(int i = 0,j = l;j <= r;i++,j++)a[j] = temp[i];
}
//2 have bug
void merge_sort2()
{
	for(int i = 2;i <= n; i *= 2)
	{
		if(n % i != 0)
		{
			for(int k = 0;k <= (i * (n / i - 1));k += i)
			{
				int l = k,j = k + i / 2,p = 0;
				while(l < k + i / 2 && j < k + i)
					if(a[l] < a[j])temp[p++] = a[l++];
					else temp[p++] = a[j++];
				while(l < k + i / 2)temp[p++] = a[l++];
				while(j < k + i)temp[p++] = a[j++];
				for(int I = 0,J = k;J < k + i;I++,J++)
				{
					a[J] = temp[I];
				}
			}
			sort(a + n - n % i,a + n);
		}
		else
		{
			for(int k = 0;k < n;k += i)
			{
				int l = k,j = k + i / 2,p = 0;
				while(l < k + i / 2 && j < k + i)
					if(a[l] < a[j])temp[p++] = a[l++];
					else temp[p++] = a[j++];
				while(l < k + i / 2)temp[p++] = a[l++];
				while(j < k + i)temp[p++] = a[j++];
				for(int I = 0,J = k;J < k + i;I++,J++)
				{
					a[J] = temp[I];
				}
			}

		}
	}

}
void bin_sort()
{
	vector<int> B[10];
	for(int i = 0; ;i++)
	{
		for(int j = 0;j < n;j++)
		{
			int wei = (a[j] / (int)(pow(10.0,i)) ) % 10;
			B[wei].push_back(a[j]);
		}
		if(B[0].size() == n)break;
		int t = 0;
		for(int k = 0;k < 10;k++)
		{
			for(int m = 0; m < B[k].size();m++)
			{
				a[t++] = B[k][m];
			}
		}
	}
}

void heap_sort()
{
	//convert a to heap
	//懒得写了，就是从最后一个有孩子的节点开始挨个调整
}
int main()
{
	n = 5;
	a[0] = 8; a[1] = 5; a[2] = 6; a[3] = 7; a[4] = 4;
	//for(int i = 0;i < n;i++)cin>> a[i];
	//bubble_sort();	
	//insert_sort1();
	//insert_sort2();
	//select_sort();
	//quick_sort(0, n - 1);
	//merge_sort1(0, n - 1);
	//merge_sort2();
	//bin_sort();
	//heap_sort();
	output();
	return 0;
}