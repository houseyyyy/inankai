#include <bits/stdc++.h>

int main()
{
    int head,end,n;
    std::cin>> head >> end >> n;
    std::vector<int> s(n,0),next(n);
    s.front() = head,s.back() = end;
    for(int i = 0; i < n; i++)std::cin>> next[i];
    for(int i = 2;i < n;i++)
    {
        if(!next[i])s[i - 1] = !head;
        else if(next[i] - next[i - 1] == 1)
        {
            s[i - 1] = s[next[i] - 1];
        }
        else if((s[i - next[i] - 1] == head) || next[i] - next[i - 1] != 1 || next[i] - next[i - 1] > 1 || next[i] > i)
        {
            std::cout << "ERROR";
            return 0;
        }
    }
    for(auto c:s)std::cout<<c;
    return 0;
}