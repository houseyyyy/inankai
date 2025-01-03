#include <bits/stdc++.h>

template <typename T>
class stack{
public:
	std::vector<T> S;
	void push(T data);
	void pop();
	T& top();
	bool empty();
	stack(){}
	friend std::ostream& operator <<(std::ostream& out,const stack<T>&my)
	{
		for(int i = 0; i < my.S.size();i++)
		{
			out << my.S[i];
		}
		return out;
	}
};
template <typename T>
void stack<T>::push(T data)
{
	S.push_back(data);
}
template <typename T>
void stack<T>::pop()
{
	S.pop_back();
}
template <typename T>
T& stack<T>::top()
{
	return S.back();
}
template <typename T>
bool stack<T>::empty()
{
	return S.empty();
}

int main()
{
	stack<char> mystack;
	std::string s;
	getline(std::cin,s);
	std::stringstream S(s);
	char c;
	while(S >> c)
	{
		
		if(mystack.empty())mystack.push(c);
		else if(mystack.top() - c == 32 ||c - mystack.top() == 32)mystack.pop();
		else mystack.push(c);
	}
	if(mystack.empty())std::cout<<"-1";
	else std::cout<<mystack;
	return 0;
}