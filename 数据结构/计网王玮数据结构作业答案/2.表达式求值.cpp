#include<iostream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;
const int INCREASE = 10;//ÿ����������10���ڴ�ռ�

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
		if (in.front() != '-')in = "+" + in;

		for (int i = 0; i < in.size(); i++)
		{
			if (in[i] == '+' || in[i] == '-')
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
		for (int i = 0; i < op.size(); i++)
		{
			S >> temp;//1/x
			if (isalpha(temp.front()))
			{
				mem.push_back(temp);
				com.push_back(op[i] + "1");
			}
			else //2 * x * y
			{
				for (int j = 0; j < temp.size(); j++)
				{
					if (temp[j] == '*' || temp[j] == '/')
					{
						com.push_back(op[i] + temp.substr(0, j));
						mem.push_back(temp.substr(j + 1));
						break;
					}
					if (j + 1 == temp.size())
					{
						mem.push_back("#");
						com.push_back(op[i] + temp);
					}
				}
			}
			//std::cout<< mem.back() << "\n";
		}
	}
	Compute operator +( Compute in)
	{
		in.combine();
		for (int i = 0; i < in.length; i++)
		{
			auto it = find(mem.begin(), mem.end(), in.mem[i]);
			if (it != mem.end())
			{
				double t = stod(com[it - mem.begin()]) + stod(in.com[i]);
				if (t >= 0)com[it - mem.begin()] = "+" + tostring(t);
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
	Compute operator -( Compute in)
	{
		in.combine();
		for (int i = 0; i < in.length; i++)
		{
			auto it = find(mem.begin(), mem.end(), in.mem[i]);
			if (it != mem.end())
			{
				double t = stod(com[it - mem.begin()]) - stod(in.com[i]);
				if (t >= 0)com[it - mem.begin()] = "+" + tostring(t);
				else com[it - mem.begin()] = tostring(t);
			}
			else
			{
				mem.push_back(in.mem[i]);
				double t = stod(in.com[i]);
				if (t >= 0)com.push_back("-" + tostring(t));
				else com.push_back("+" + tostring(0 - t));
				length++;
			}
		}
		return *this;
	}
	Compute operator *( Compute in)
	{
		in.combine();
		Compute ans;
		for (int i = 0; i < in.length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				double t = stod(com[j]) * stod(in.com[i]);
				if (in.mem[i] == "#")
				{
					if (mem[j] != "#")ans.mem.push_back(mem[j]);
					else ans.mem.push_back("#");
				}
				else
				{
					if (mem[j] != "#")ans.mem.push_back(mem[j] + "*" + in.mem[i]);
					else ans.mem.push_back(in.mem[i]);
				}
				if (t >= 0)ans.com.push_back("+" + tostring(t));
				else ans.com.push_back(tostring(t));
				ans.length++;
			}
		}
		return ans;
	}

	Compute operator /(const Compute in)
	{
		Compute ans;
		for (int i = 0; i < in.length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				try
				{
					if (stod(in.com[i]) == 0)throw stod(in.com[i]);
				}
				catch (double)
				{
					cerr << "devide zero";
					exit(1);
				}
				
					double t = stod(com[j]) / stod(in.com[i]);
				
				if (in.mem[i] == "#")
				{
					if (mem[j] != "#")ans.mem.push_back(mem[j]);
					else ans.mem.push_back("#");
				}
				else
				{
					if (mem[j] != "#")ans.mem.push_back(mem[j] + "/" + in.mem[i]);
					else ans.mem.push_back("/" + in.mem[i]);
				}
				if (t >= 0)ans.com.push_back("+" + tostring(t));
				else ans.com.push_back(tostring(t));
				ans.length++;
			}
		}
		return ans;
	}
	void combine()
	{
		for (int i = 0; i < length; i++)
		{
			if (com[i] == "+0" || com[i] == "-0" || com[i] == "0"&&mem[i]!="#")
			{
				com.erase(com.begin() + i);
				mem.erase(mem.begin() + i);
				length--;
				i--;
			}

		}
		
	}
	friend std::ostream& operator <<(std::ostream& out, Compute& in)
	{
		in.combine();
		if (!in.length)
		{
			out << "0";
			return out;
		}
		for (int i = 0; i < in.length; i++)
		{
			std::string temp = "*";
			if (in.mem[i].front() == '/')temp.clear();

			if (!i && in.com[i].front() == '+')
			{
				if (stod(in.com[i]) == 1 && in.mem[i] != "#")std::cout << in.mem[i];
				else if (stod(in.com[i]) == -1 && in.mem[i] != "#") std::cout << "-" << in.mem[i];
				else
				{
					if (in.mem[i] != "#")std::cout << stod(in.com[i]) << temp << in.mem[i];
					else std::cout << stod(in.com[i]);
				}
			}
			else if ((stod(in.com[i]) == 1 || stod(in.com[i]) == -1) && in.mem[i] != "#")
			{
				if (stod(in.com[i]) == 1)std::cout << "+";
				else std::cout << "-";
				std::cout << in.mem[i];
			}
			else if (in.mem[i] == "#")
			{
				std::cout << in.com[i];
			}
			else std::cout << in.com[i] << temp << in.mem[i];
		}
		return out;
	}
};
//��double����תΪstring λ���ܶ�ᱣ������λ���������Ǻ�����
string tostring(double n)
{
	ostringstream s;
	s << n;
	return s.str();
}

//�ִ��ջ
template <class T>
class Stack final
{
public:
	T* data;
	int nowtop;//��ǰջ��
	int length;//��ǰջ��Ԫ�ض���
	bool isfull;//�ж������Ƿ���
	int MaxSize;//�������
	Stack()//�չ��캯��
	{
		data = nullptr;//��ʼΪ��ָ��
		nowtop = -1;//ջ��Ϊ-1
		length = 0;//����Ϊ0
		MaxSize = 0;//����Ϊ0
		isfull = true;//��ʼֵΪtrue
	}
	void push(T tem)//��ջ
	{

		if (isfull)//�ж��Ƿ���Ҫ����
		{
			T* t = new T[MaxSize + INCREASE];//�����������ӿռ�
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
	void pop()//��ջ
	{
		nowtop--;
		length--;
	}
	T top()//��ȡջ��
	{
		if (nowtop == -1)return  data[0];
		else return data[nowtop];
	}
	bool empty()
	{
		return nowtop == -1 ? true : false;//ջ��Ϊ-1��Ϊ��
	}
	int size()//ͳ��ջ��Ԫ��
	{
		return length;
	}
};

//�����������ȼ�
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


//�ַ����Ƿ��������
bool isfuhao(const string s)
{
	if (s == "+" || s == "-" || s == "*" || s == "/")return true;
	return false;
}

//��׺���ʽת��׺���ʽ
string topostfix(string temp)
{
	Stack<char> op;//�洢������
	string ans;
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i] == ' ')continue;
		if (temp[i] == '(')//������ֱ����ջ
		{
			op.push(temp[i]);
		}
		else if (isalpha(temp[i]) || isdigit(temp[i]) || temp[i] == '.')
		{
			if (isalpha(temp[i]) && !ans.empty() && (ans.back() == '.' || isdigit(ans.back()) || isalpha(ans.back())))return "False";
			if (isdigit(temp[i]) && !ans.empty() && isalpha(ans.back()))return "False";
			if (temp[i] == '.' && !ans.empty() && ans.back() == '.')return "False";
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
					ans = ans + ' ';
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
			else return "False";
		}
		else return "False";
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
	if (postfix == "False")return "False";
	Stack<Compute>  num;

	string t;
	stringstream S(postfix);//תΪ�ַ�����

	while (S >> t)
	{
		if (!isfuhao(t))
		{
			Compute temp(t);
			num.push(temp);
		}
		else if (t == "(")return "False";
		else
		{	
			if (num.size() == 1 && t[0] == '-')
			{
				Compute temp("0");
				Compute c = num.top(); num.pop();
				num.push(temp - c);
				continue;
			}
			else if (num.size() < 2)return "False";
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
	if (num.size() != 1)return "False";
	if (!num.empty())
	{
		Compute ans = num.top(); num.pop();
		ostringstream s;
		s << ans;
		return s.str();

	}
	else return "False";
}

int main()
{
	string s;
	getline(std::cin, s);
	string S = topostfix(s);
	string ans = calculate(S);
	if (S != "False" && ans != "False")
	{
		
		//std::cout << S << endl;//��׺���ʽ
		std::cout << ans << endl;
		std::cout << "True" << endl;
	}
	else
	{
		std::cout << "False";
	}

	return 0;
}