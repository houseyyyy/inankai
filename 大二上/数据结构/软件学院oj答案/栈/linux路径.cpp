#include <bits/stdc++.h>

int main()
{
	std::stack<char> s;
	char c;
	std::string now;
	std::string temp;
	getline(std::cin,temp);
	std::stringstream T(temp);
	while(T >> c)
	{
		if(s.empty())s.push(c);
		else
		{
			if(isalpha(c))s.push(c);
			else if(c == '/' && s.top()!='/')
			{
				if(s.top() == '.')
				{
					s.pop();
					s.pop();
				}
				s.push(c);
			}
			else if(c == '.')
			{
				if(s.top()!= '.')
				{
					s.push('.');
				}
				else
				{	s.pop();
					if(s.size() == 1)continue;
					s.pop();
					while(s.top()!= '/' && s.size() > 0)s.pop();
				}
			}
		}
	}
	while(!s.empty())
	{
		now = now + s.top();
		s.pop();
	}
	reverse(now.begin(),now.end());
	if(now.size() > 1&& now.back() == '/')now.pop_back();
	std::cout<< now;
	return 0;
}