#include <bits/stdc++.h>
#define INPUT 1
class Tri
{
public:
	std::map<std::pair<int,int> , int> thr;
	int n,m,lens;
	Tri(int k)
	{
		std::cin>> n >> m >> lens;
		for(int i = 0;i < lens;i++)
		{	
			int x,y,z;
			std::cin>> x >> y >> z;
			thr[{x,y}] = z;
		}
	}
	Tri()
	{
		n = m = lens = 0;
	}
};
void multi(Tri a,Tri b)
{
	if(a.n != b.m)
	{
		std::cout<< "ERROR";return ;
	}
	Tri ans;
	ans.n = a.n;ans.m = b.m;
	for(auto k:a.thr)
	{
		int t = k.first.second;
		//std::cout<< t;
		for(auto d:b.thr)
		{
			int y = d.first.first;
			if(t == y)
			{
				ans.thr[{k.first.first,d.first.second}] += k.second * d.second;
			}
		}
	}
	if(ans.thr.empty())
	{
		std::cout<<"The answer is a Zero Matrix";
		return ;
	}
	for(auto c:ans.thr)
	{
		std::cout<< c.first.first<<' '<<c.first.second << ' ' << c.second <<"\n";
	}
}
int main()
{
	Tri a(INPUT),b(INPUT);
	multi(a,b);
	return 0;
}