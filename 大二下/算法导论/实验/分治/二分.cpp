#include <bits/stdc++.h>

using namespace std;
int main()
{
    string n;
    getline(std::cin,n);
    vector<int> v;
    stringstream s(n);
    int temp;
    while(s >> temp){
        v.push_back(temp);
    }
    cin>> temp;
    int l = 0, r = v.size() - 1;
    //cout<< temp << l <<r;
    while(l < r)
    {
        int mid = (l + r) / 2;
        if(v[mid] > temp)r = mid;
        else if(v[mid] == temp)
        {
            cout<< mid;
            return 0;
        }
        else l = mid + 1;
    }
    if(v.back() == temp)cout<< v.size() - 1;
    else cout<< -1;
    return 0;
}