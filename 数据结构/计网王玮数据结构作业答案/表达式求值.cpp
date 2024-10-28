#include<bits/stdc++.h>
using namespace std;
const int INCREASE = 10;//每次扩容增加10个内存空间

string calculate(string);
std::string tostring(double);
class Compute
{
public:
	int length;
	std::vector<std::string> mem;
	std::vector<std::string> com;
	Compute()
	{
		length = 0;
	}
	Compute(std::string in)
	{
		std::vector<std::string> op;
		if(in.front() != '-')in = "+" + in;

		for(int i = 0;i < in.size();i++)
		{
			if(in[i] == '+' || in[i] == '-')
			{
				std::string t;
				t.push_back(in[i]);
				op.push_back(t);
				in[i] = ' ';
			}
		}
		length = op.size();
		std::stringstream S(in);
		std::string temp;
		for(int i = 0; i < op.size();i++)
		{
			S >> temp;//1/x
			if(isalpha(temp.front()))
			{
				mem.push_back(temp);
				com.push_back(op[i] + "1");
			}
			else //2 * x * y
			{
				for(int j = 0;j < temp.size();j++)
				{
					if(temp[j] == '*' || temp[j] == '/')
					{
						com.push_back(op[i] + temp.substr(0,j));
						mem.push_back(temp.substr(j + 1));
						break;
					}
					if(j + 1 == temp.size())
					{
						mem.push_back("#");
						com.push_back(op[i] + temp);
					}	
				}
			}
			//std::cout<< mem.back() << "\n";
		}
	}
	Compute operator +(const Compute in)
	{
		for(int i = 0; i < in.length;i++)
		{
			auto it = find(mem.begin(),mem.end(),in.mem[i]);
			if(it != mem.end())
			{
				double t = stod(com[it - mem.begin()]) + stod(in.com[i]);
				if(t >= 0)com[it - mem.begin()] = "+" + tostring(t);
				else com[it - mem.begin()] = "-" + tostring(t);
			}
			else
			{
				mem.push_back(in.mem[i]);
				com.push_back(in.com[i]);
				length++;
			}
		}
		return *this;
	}
	Compute operator -(const Compute in)
	{
		for(int i = 0; i < in.length;i++)
		{
			auto it = find(mem.begin(),mem.end(),in.mem[i]);
			if(it != mem.end())
			{
				double t = stod(com[it - mem.begin()]) - stod(in.com[i]);
				if(t >= 0)com[it - mem.begin()] = "+" + tostring(t);
				else com[it - mem.begin()] = tostring(t);
			}
			else
			{
				mem.push_back(in.mem[i]);
				double t = stod(in.com[i]);
				if(t >= 0)com.push_back("-" + tostring(t));
				else com.push_back("+" + tostring(0 - t));
				length++;
			}
		}
		return *this;
	}
	Compute operator *(const Compute in)
	{
		Compute ans;
		for(int i = 0; i < in.length;i++)
		{
			for(int j = 0; j < length;j++)
			{
				double t = stod(com[j]) * stod(in.com[i]);
				if(in.mem[i] == "#")
				{
					if(mem[j] != "#")ans.mem.push_back(mem[j]);
					else ans.mem.push_back("#");
				}
				else
				{
					if(mem[j] != "#")ans.mem.push_back(mem[j] + "*" + in.mem[i]);
					else ans.mem.push_back(in.mem[i]);
				}
				if(t >= 0)ans.com.push_back("+" + tostring(t));
				else ans.com.push_back(tostring(t));
				ans.length ++;
			}
		}
		return ans;
	}

	Compute operator /(const Compute in)
	{
		Compute ans;
		for(int i = 0; i < in.length;i++)
		{
			for(int j = 0; j < length;j++)
			{
				double t = stod(com[j]) / stod(in.com[i]);
				if(in.mem[i] == "#")
				{
					if(mem[j] != "#")ans.mem.push_back(mem[j]);
					else ans.mem.push_back("#");
				}
				else
				{
					if(mem[j] != "#")ans.mem.push_back(mem[j] + "/" + in.mem[i]);
					else ans.mem.push_back("/" + in.mem[i]);
				}
				if(t >= 0)ans.com.push_back("+" + tostring(t));
				else ans.com.push_back(tostring(t));
				ans.length ++;
			}
		}
		return ans;
	}
	void combine()
	{
		for(int i = 0; i < length;i++)
		{
			if(com[i] == "+0" || com[i] == "-0" || com[i] == "0")
			{
				com.erase(com.begin() + i);
				mem.erase(mem.begin() + i);
				length--;
				i--;
			}
		}
	}
	friend std::ostream& operator <<(std::ostream& out,Compute& in)
	{
		in.combine();

		for(int i = 0; i < in.length;i++)
		{
			std::string temp = "*";
			if(in.mem[i].front() == '/')temp.clear();

			if(!i && in.com[i].front() == '+')
			{
				if(stod(in.com[i]) == 1 && in.mem[i] != "#")std::cout << in.mem[i];
				else if(stod(in.com[i]) == -1 && in.mem[i] != "#") std::cout<< "-" << in.mem[i];
				else 
				{
					if(in.mem[i] != "#")std::cout<< stod(in.com[i]) << temp << in.mem[i];
					else std::cout<< stod(in.com[i]);
				}
			}
			else if( (stod(in.com[i]) == 1 || stod(in.com[i]) == -1) && in.mem[i] != "#")
			{
				if(stod(in.com[i]) == 1)std::cout<<"+";
				else std::cout<<"-";
				std::cout<< in.mem[i];
			}
			else if(in.mem[i] == "#")
			{
				std::cout<< in.com[i];
			}
			else std::cout<< in.com[i] << temp << in.mem[i];
		}
		return out;
	}
};
//将double类型转为string 位数很多会保留到六位，正常都是合理保留
string tostring(double n)
{
	ostringstream s;
	s << n;
	return s.str();
}

//手搓的栈
template <class T>
class Stack final
{
public:
	T *data;
	int nowtop;
	int length;
	bool isfull;
	int MaxSize;
	Stack()//空构造函数
	{
		data = nullptr;
		nowtop = -1;
		length = 0;
		MaxSize = 0;
		isfull = true;
	}
	void push(T tem)//入栈
	{

		if (isfull)//判断是否需要扩容
		{
			T* t = new T[MaxSize + INCREASE];
			MaxSize = MaxSize + INCREASE;
			for (int i = 0; i < length; i++)
			{
				t[i] = data[i];
			}
			data = t;
			isfull = false;
		}

		data[++nowtop] = tem;
		length++;
		if (nowtop + 1 == MaxSize)isfull = true;
		
	}
	void pop()//出栈
	{
		nowtop--;
		length--;
	}
	T top()//获取栈顶
	{
		if (nowtop == -1)return  data[0];
		else return data[nowtop];
	}
	bool empty()
	{
		return nowtop == -1 ? true : false;
	}
	int size()//统计栈中元素
	{
		return length;
	}
};

//获得运算符优先级
int getlevel(const char op)
{
	switch (op)
	{
		case '*':
		case '/':return 2;
		case '+':
		case '-':return 1;
	}
	return 0;
}


//字符串是否是运算符
bool isfuhao(const string s)
{
	if (s == "+" || s == "-" || s == "*" || s == "/")return true;
	return false;
}

//中缀表达式转后缀表达式
string topostfix(string temp)
{
	Stack<char> op;
	string ans;
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i] == ' ')continue;
		if (temp[i] == '(')//左括号直接入栈
		{
			op.push(temp[i]);
		}
		else if (isalpha(temp[i]) || isdigit(temp[i]) || temp[i] == '.')
		{
			if(isalpha(temp[i]) && !ans.empty() && (ans.back() == '.' || isdigit(ans.back()) || isalpha(ans.back())) )return "error";
			if(isdigit(temp[i]) && !ans.empty() && isalpha(ans.back()))return "error";
			if(temp[i] == '.' && !ans.empty() && ans.back() == '.')return "error";
			ans = ans + temp[i];
		}
		else if (getlevel(temp[i]) > 0)
		{
			ans += ' ';
			if (op.empty())
			{
				op.push(temp[i]);
			}
			else if (getlevel(temp[i]) > getlevel(op.top()))
			{
				op.push(temp[i]);
			}
			else if (getlevel(temp[i]) <= getlevel(op.top()))
			{
				while (!op.empty() && getlevel(temp[i]) <= getlevel(op.top()))
				{
					ans = ans + op.top();
					ans = ans +  ' ';
					op.pop();
				}
				op.push(temp[i]);
			}
		}
		else if (temp[i] == ')')
		{
			while (!op.empty() && op.top() != '(')
			{
				ans = ans + ' ';
				ans = ans + op.top();
				op.pop();
			}
			if (!op.empty() && op.top() == '(')op.pop();
			else return "error";
		}
		else return "error";
	}
	while (!op.empty())
	{
		ans += ' ';
		ans += op.top();
		op.pop();
	}
	return ans;
}

string calculate(string postfix)
{
	if(postfix == "error")return "error";
	Stack<Compute>  num;

	string t;
	stringstream S(postfix);//转为字符串流

	while (S >> t)
	{
		if (!isfuhao(t))
		{
			Compute temp(t);
			num.push(temp);
		}
		else if(t == "(")return "error";
		else
		{	
			if(num.size() < 2)return "error";
			Compute a = num.top(); num.pop();
			Compute b = num.top(); num.pop();
			switch (t[0])
			{
			case '+':num.push(a + b); break;
			case '-':num.push(b - a); break;
			case '*':num.push(a * b); break;
			case '/':num.push(b / a); break;
 			}
			
		}
	}
	if(num.size() != 1)return "error";
	if (!num.empty())
	{
		Compute ans =  num.top();num.pop();
		ostringstream s;
		s << ans;
		return s.str();

	}
	else return "error";
}

int main()
{
	string s;
	getline(std::cin,s);
	string S = topostfix(s);
	std::cout<< S <<"\n";
	string ans = calculate(S);
	if(ans != "error")
	std::cout<< ans << "\n";
	else std::cout<< ans;
	return 0;
}