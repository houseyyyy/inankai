#include <bits/stdc++.h>

int main()
{
	std::string s;
	std::cin>> s;
	for(int i = 0; i + 1 < s.size();i++)
	{
		if(s[i+1] == s[i]||s[i+1] - s[i] == 32 || s[i+1] - s[i] == -32)
		{
			s.erase(s.begin() + i,s.begin() + i + 2);
			i = -1;
		}
	}
	if(s.empty())std::cout<<"-1";
	else std::cout<< s;
	return 0;
}