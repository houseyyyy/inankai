#include <bits/stdc++.h>


int main()
{
    int N,Ssize;
    char l,r;
    std::cin >> N >> Ssize >> l >> r;

    std::mt19937 rand(std::random_device{}());
    std::uniform_int_distribution cre((int)l,(int)r);
    std::fstream out("test.txt",std::ios::in | std::ios::out | std::ios::trunc);
    if(out.is_open())
    {
        for(int i = 0; i < N;i++)
        {
            for(int j = 0;j < Ssize;j++)
            {
                out << char(cre(rand));
            }
            out<<"\n";
        }
        
    }
    else throw std::runtime_error("bad open file");
    out.close();
    return 0;
}