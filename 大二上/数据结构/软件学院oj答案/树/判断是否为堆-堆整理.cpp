#include <bits/stdc++.h>

bool ismaxheap(int* data,int size)
{
	int pos = size / 2;
	int i;
	for(i = pos;i > 0;i--)
	{
		if((i * 2 + 1 ) <= size && data[i * 2  + 1] > data[i])break;
		if(data[i * 2] > data[i])break;
	}
	if(i)return false;
	else return true;
}
bool isminheap(int* data,int size)
{
	int pos = size / 2;
	int i;
	for(i = pos;i > 0;i--)
	{
		if( (i*2 + 1 )<= size && data[i * 2  + 1] < data[i])break;
		if(data[i * 2] < data[i])break;
	}
	if(i)return false;
	else return true;
}
void tomaxheap(int*& data,int size)
{
	int pos = size / 2;
	int i = pos;
	for(;i > 0;i --)
	{	
		int j = i;
		while(j <= pos && (data[j] < data[2 * j] || ((2 * j + 1) <= size &&  data[j] < data[2 * j + 1])) )
		{
			if((2 * j + 1) <=size && data[2 * j] <= data[2 * j + 1])
			{
				std::swap(data[j],data[2 * j + 1]);
				j = 2 * j + 1;
			}
			else 
			{
				std::swap(data[j],data[2 * j]);
				j = 2 * j;
			}
		}
	}
	for(int k = 1; k <= size; k++)
	{
		std::cout << data[k] << " \n"[k == size];
	}
}
void tominheap(int*& data,int size)
{
	int pos = size / 2;
	int i = pos;
	for(;i > 0;i --)
	{	
		int j = i;
		while(j <= pos && (data[j] > data[2 * j] ||( (2 * j + 1) <= size && data[j] > data[2 * j + 1])) )
		{
			if((2 * j + 1) <=size && data[2 * j] >= data[2 * j + 1])
			{
				std::swap(data[j],data[2 * j + 1]);
				j = 2 * j + 1;
			}	
			else 
			{
				std::swap(data[j],data[2 * j]);
				j = 2 * j;
			}
		}
	}
	for(int k = 1; k <= size; k++)
	{
		std::cout << data[k] << " \n"[k == size];
	}
}
int main()
{
	int size;
	std::cin>>size;
	int *data = new int[size + 1];
	for(int i = 1;i <= size;i++)
	{
		std::cin>> data[i];
	}
	if(ismaxheap(data,size) && isminheap(data,size))
	{
		std::cout<< "max min ";
	}
	else if(ismaxheap(data,size))
	{
		std::cout<< "max ";
		tominheap(data,size);
	}
	else if(isminheap(data,size))
	{
		std::cout<<"min ";
		tomaxheap(data,size);
	}
	else tomaxheap(data,size);
	return 0;
}