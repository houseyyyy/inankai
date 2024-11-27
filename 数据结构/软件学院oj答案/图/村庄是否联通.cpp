#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[25][25];

int main()
{
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
    int x,y;
    cin>>x>>y;
    a[x][y]=a[y][x]=1;
    }
    cin>>m;
    for(int i=0;i<m;i++)
    {   
        bool is=false;
        bool b[25];
        for(int w = 0;w< 25;w++)b[w]=false;
        int x,y;
        cin >>x>>y;
        queue<int> q;
        q.push(x);
        b[x]=true;
        while(!q.empty())
        {
            int k= q.front();
            q.pop();
            for(int j=0;j<n;j++)
            {
                if(a[k][j]&&!b[j])
                {
                    q.push(j);
                    b[j]=true;
                    if(j==y)is=true;
                }
            }
        }
        if(is)cout<<"true";
        else cout<<"false";
        cout<<endl;
    }
    return 0;
}