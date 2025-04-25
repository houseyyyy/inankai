#include <bits/stdc++.h>
using namespace std;

int  quick_sort(vector<int> q,int l,int r,int k){
    if(l == r)return q[l];
    int i=l-1, j=r+1,random=rand()%(r-l+1)+l,x=q[random];
    while(i<j){
        do i++;while(q[i]<x);
        do j--;while(q[j]>x);
        if(i<j)swap(q[i],q[j]);
    }
    if(j - l + 1 >= k)return quick_sort(q,l,j,k);
    else return quick_sort(q,j+1,r,k - j + l - 1);
}
int main(){
    string t;
    getline(cin,t);
    stringstream s(t);
    vector<int> v;
    int x;
    while(s >> x)v.push_back(x);
    cin>> x;
    
    cout<<quick_sort(v,0,v.size() - 1,x);
    return 0;
}