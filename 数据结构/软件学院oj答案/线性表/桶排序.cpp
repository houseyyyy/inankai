#include <bits/stdc++.h>

int main()
{
    int N,max = 0;
    std::cin>> N;
    std::vector<int> a(N);
    for(int i = 0; i < N;i++)
    {
        std::cin>> a[i];
        if(a[i] > max)max = a[i];
    }
    int maxtimes = log10(max) + 1;
    //std::cout<< maxtimes;
    std::vector<std::vector<int> > bin(10);
    for(int k = 0;k < maxtimes;k++)
    {
        for(int i = 0; i < N;i++)
        {
            int temp = a[i] / (int)pow(10,k) % 10;
            bin[temp].push_back(a[i]);
        }
        int t = 0;
        for(int j = 0;j < 10;j++)
        {
            for(int l = 0;l < bin[j].size();l++)
            {
                a[t++] = bin[j][l];
            }
            bin[j].clear();
        }
        for(int m = 0; m < N;m++)
        {
            std::cout<< a[m] << " \n"[m + 1 == N];
        }
    }
    return 0;
}