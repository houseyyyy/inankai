#include <bits/stdc++.h>

using namespace std;
int n,k;
int** muti(int** a,int** b)
{
    int** res = new int*[n];
    for(int i = 0;i < n;i++)res[i] = new int[n];
    for(int i = 0;i < n;i++)
    {
        for(int j = 0;j < n;j++)
        {
            long long sum = 0;
            for(int m = 0;m < n;m++)
            {
                sum += (a[i][m]*1LL*b[m][j]);
                sum = sum % 1000000007;
            }
            res[i][j] = sum;
        }
    }
    return res;
}
int** p(int** A,int b)
{
    int** res = new int*[n];
    for (int i = 0; i < n; i++)
    {
        res[i] = new int[n];
        for (int j = 0; j < n; j++) res[i][j] = (i==j);  // 单位矩阵
    }
    while(b > 0)
    {
        if(b & 1)res = muti(res,A);
        A = muti(A,A);
        b /= 2;
    }
    return res;
}
int main()
{
    cin>> n >> k;
    int** A = new int*[n];
    for(int i = 0;i < n;i++)A[i] = new int[n];
    for(int i = 0;i < n;i++)
    {
        for(int j = 0;j < n;j++)
        {
            cin>> A[i][j];
        }
    }    
    int ** ans = p(A,k);
    for(int i = 0;i < n;i++)
    {
        for(int j = 0;j < n;j++)
        {
            cout<< ans[i][j] << " \n"[j + 1 == n];
        }
    }
    return 0;
}