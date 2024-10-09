#include <bits/stdc++.h>

int get_Level(char& op)
{
	if(op == '^')return 4;
	if(op == '*' || op == '/')return 3;
	if(op == '%')return 2;
	if(op == '+' || op == '-')return 1;
	return 0;
}
std::string to_Postfix(std::string& now)
{	
	std::string ans;
	std::stack<char> op_Stack;
	op_Stack.push('#');

	for(int i = 0;i < (int)now.size();i++)
	{
		if(now[i] == '#')return "ERROR IN INFIX NOTATION";

		if(isdigit(now[i]) || now[i] == '.')ans.push_back(now[i]);
		else if(now[i] == '(')op_Stack.push(now[i]);
		else if(now[i] == ')')
		{
			ans.push_back(' ');
			while(op_Stack.top() != '#' && op_Stack.top() != '(')
			{
				ans.push_back(op_Stack.top());
				op_Stack.pop();
			}
			if(op_Stack.top() == '(')op_Stack.pop();
			else return "ERROR IN INFIX NOTATION";
			
		}
		else if(get_Level(now[i]) > get_Level(op_Stack.top()))
		{
			ans.push_back(' ');
			op_Stack.push(now[i]);
		}
		else 
		{	
			ans.push_back(' ');
			while(get_Level(now[i]) <= get_Level(op_Stack.top()))
			{
				ans.push_back(op_Stack.top());
				ans.push_back(' ');
				if(op_Stack.top() != '#')op_Stack.pop();
			}
			op_Stack.push(now[i]);
		}
	}
	while(op_Stack.top() != '#')
	{
		ans.push_back(' ');
		ans.push_back(op_Stack.top());
		op_Stack.pop();
	}
	return ans;
}
double calculate_Postfix(std::string &postfix)
{	
	std::stack<double> num;
	std::string t;
	for(int i = 0;i < (int)postfix.size();i++)
	{
		//check
		if(postfix[i] == '(')
		{
			postfix = "ERROR IN INFIX NOTATION";
			return false;
		}
		
		if(isdigit(postfix[i]) || postfix[i] == '.')
		{
			t.push_back(postfix[i]);
		}
		else if(postfix[i] == ' ')
		{
			if(!t.empty())
			{
				num.push(stod(t));
				t.clear();
			}
		}
		else
		{	
			//check
			if(num.size() < 2)
			{
				postfix = "ERROR IN INFIX NOTATION";
				return false;
			}

			double a,b;
			a = num.top();
			num.pop();
			b = num.top();
			num.pop();
			switch(postfix[i])
            {
            	case '+':num.push(b+a);break;
            	case '-':num.push(b-a);break;
            	case '*':num.push(b*a);break;
            	case '/':num.push(b/a);break;
            	case '%':num.push(double((int)b%(int)a));break;
            	case '^':num.push(pow(b,a));break;
            }
		}
	}
	//check
	if(num.size() != 1)
	{
		postfix = "ERROR IN INFIX NOTATION";
		return false;		
	}
	return num.top();
}
int main()
{
	std::string s;
	std::cin >> s;
	std::string postfix = to_Postfix(s);
	double ans = calculate_Postfix(postfix);

	if(postfix != "ERROR IN INFIX NOTATION")
	{ 
		std::cout<<std::fixed<<std::setprecision(2) << ans;
	}
	else std::cout<< postfix;
	return 0;
}