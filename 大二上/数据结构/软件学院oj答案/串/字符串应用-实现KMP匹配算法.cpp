#include <bits/stdc++.h>

int main()
{
	bool isfind = 0;
	std::string s,p;
	std::cin>> s >> p;
	std::vector<int> pmt(p.size(),0);
	for(int i = 1,j = 0;i < p.size();i++)
	{
		while(j && p[i] != p[j])j = pmt[j - 1];
		if(p[i] == p[j])j++;
		pmt[i] = j;
	}
	//for(auto c : pmt)std::cout<< c;
	for(int i = 0,j = 0;i < s.size() && !isfind;i++)
	{
		while(j && s[i] != p[j])j = pmt[j - 1];
		if(s[i] == p[j])j++;
		if(j == p.size())
		{
			std::cout<< i - j + 1;
			isfind = true;
		}
	}
	if(!isfind)std::cout<<"no";	
	return 0;
}