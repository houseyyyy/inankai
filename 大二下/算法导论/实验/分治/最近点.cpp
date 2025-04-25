#include <bits/stdc++.h>

using namespace std;
int n,m;
double dis(pair<double,double> a,pair<double,double> b)
{
    return sqrt((a.first - b.first)*(a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}
double MinDis(vector<pair<double,double> > p,double* x,double* y)
{
    if(p.size() <= 3)
    {
        return min(dis(p[0],p[1]),min(dis(p[0],p[2]),dis(p[1],p[2])));
    }
    sort(p.begin(),p.end());
    int mid = p.size() / 2;
    vector<pair<double,double>> pL,pR;
    pL.assign(p.begin(),p.begin() + mid);
    pR.assign(p.begin() + mid,p.end());
    double* xL = new double[pL.size()];
    double* yL = new double[pL.size()];
    double* xR = new double[pR.size()];
    double* yR = new double[pR.size()];
    for(int i = 0;i < pL.size();i++)
    {
        xL[i] = pL[i].first;yL[i] = pL[i].second;
    }      
    for(int i = 0;i < pR.size();i++)
    {
        xR[i] = pR[i].first;yR[i] = pR[i].second;
    } 
    double minL = MinDis(pL,xL,yL);
    double minR = MinDis(pR,xR,yR);
    double mintotal = min(minL,minR);
    double l = p[mid].first;
    for(int i = mid;i < p.size();i++)
    {
        if(p[i].first - l < mintotal)
        {
            for(int j = mid - 1;j >= 0;j--)
            {
                if(l - p[j].first < mintotal)
                {
                    mintotal = min(mintotal,dis(p[i],p[j]));
                }
                else break;
            }
        }
        else break;
    }
    return mintotal;
}
int main()
{
    cin>> n;
    vector<pair<double,double> >p;
    double* x = new double[n];
    double* y = new double[n];
    int flag = 0;
    while(n--)
    {
        double X,Y;
        cin>> X >> Y;
        x[flag] = X;y[flag] = Y;flag++;
        p.push_back({X,Y});
    }
    printf("%.4lf",MinDis(p,x,y));
    return 0;
}