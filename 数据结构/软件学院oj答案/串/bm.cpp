#include <bits/stdc++.h>


int main()
{

	std::fstream out("test.txt");
	out.seekg(0);
	std::string s,p;

	std::cin>> p;

	bool ismatched = false;
	while(std::getline(out,s)){
		ismatched = false;
		std::chrono::high_resolution_clock::time_point start;
    	std::chrono::high_resolution_clock::time_point finish;
    	start = std::chrono::high_resolution_clock::now(); // 开始计时
		std::unordered_map<char,int> BC;
		for(int i = 0;i < s.size();i++)
		{
			BC.insert({s[i],-1});
		}
		for(int i = 0;i < p.size();i++)
		{
			BC[p[i]] = i;
		}

		std::vector<int> ss(p.size());
		for(int i = p.size() - 1;i >= 0;i--)
		{
			int j = i,k = p.size() - 1;
			while(p[j] == p[k])
			{
				j--;k--;
			}
			if(i == p.size() - 1)ss[i] = p.size();
			else ss[i] = p.size() - 1 - k;
		}

		std::vector<int> gs(p.size(),p.size());
		int m = p.size(),n = s.size();
		//m - j - 1 = 已经匹配的字符后缀长度
		for(int i = 0,j = m - 1;j >= 0;j --)
		{
			if(ss[j] == j + 1)
			{
				for(;i < m - j - 1;i++)
				{
					gs[i] = m - j - 1;
				}
			}
		}

		for(int j = 0; j < m - 1;j++)gs[m - ss[j] - 1] = m - j - 1;
		int i = 0,j = 0;
		while (i <= n - m) 
		{
			for (j = m - 1; j >= 0 && p[j] == s[i + j]; --j);
				if (j < 0) 
				{
					ismatched = true;
					std::cout<<"matched position:"  << i;

					break;
					//i += gs[0];
				}
				else i += std::max(gs[j], BC[s[i + j]]);
		}
		if(!ismatched)std::cout<< "can't find";
		finish = std::chrono::high_resolution_clock::now(); // 结束计时
		std::cout << "time:" << std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count() << "us.\n";
	}
	out.close();
	return 0;
}