#include <bits/stdc++.h>

using namespace std;

int a[110],b[110],c[110],d[110];
int n;

bool same(int* q,int* w)
{
	for(int i = 0; i < n;i++)
	if(q[i] != w[i])return false;
	return true;
}
bool insert()
{
	bool t = false;
	for(int i = 1;i < n;i++)
	{
		if(same(a,b))t = true;
		for(int j = i - 1;j >= 0;j --)
		{
			if(a[j] > a[j + 1])swap(a[j],a[j + 1]);
		}
		if(t)
		{
			cout<<"Insertion Sort" << endl;
			for(int i = 0;i < n;i++)
			{
				cout<< a[i] << " \n"[i + 1 == n];
			}
			return true;
		}
	}
	return false;
}
void merge(int* a)
{
	bool t = false;
	for(int i = 2;i <= n; i *= 2)
	{
		if(n % i != 0)
		{
			for(int k = 0;k <= (i * (n / i - 1));k += i)
			{
				int l = k,j = k + i / 2,p = 0;
				while(l < k + i / 2 && j < k + i)
					if(a[l] < a[j])d[p++] = a[l++];
					else d[p++] = a[j++];
				while(l < k + i / 2)d[p++] = a[l++];
				while(j < k + i)d[p++] = a[j++];
				for(int I = 0,J = k;J < k + i;I++,J++)
				{
					a[J] = d[I];
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
					if(a[l] < a[j])d[p++] = a[l++];
					else d[p++] = a[j++];
				while(l < k + i / 2)d[p++] = a[l++];
				while(j < k + i)d[p++] = a[j++];
				for(int I = 0,J = k;J < k + i;I++,J++)
				{
					a[J] = d[I];
				}
			}

		}
		if(t)
		{
			cout<<"Merge Sort" << endl;
			for(int i = 0;i < n;i++)
			{
				cout<< a[i] << " \n"[i + 1 == n];
			}
			return;
		}

		if(same(a,b))t = true;
	}

}
int main()
{
	cin>> n;
	for(int i = 0;i < n;i++)
	{	
		cin>> a[i];
		c[i] = a[i];
	}
	for(int i = 0;i < n;i++)cin>> b[i];
	if(!insert())
	{
		merge(c);
	}
	return 0;
}