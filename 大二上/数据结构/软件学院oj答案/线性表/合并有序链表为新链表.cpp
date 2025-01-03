#include <bits/stdc++.h>

class list
{
public:
    int num;
    list* next;
    list(int _num):num(_num){next = NULL;}
    list(){next = NULL;}
};

void insert(list* &head,list* &node,int position)
{   
    int flag = 0;
    for(auto i = head; i;i = i->next,flag++)
    {
        if(flag == position)
        {
            node->next = i->next;
            i->next = node;
            return;
        }
    }
}
void display(list* &head)
{
    for(auto i = head->next;i;i = i->next)
    {
        std::cout<<i->num;
        if(i)std::cout<<" ";
    }
}
int main()
{
    int n,m;
    std::cin>> n >> m;
    list* head = new list;
    int t;
    for(int i = 0;i < n;i++)
    {
        std::cin >> t;
        auto temp =  new list(t);
        insert(head,temp,i);
    }
    for(int i = 0;i < m;i++)
    {
        std::cin>> t;
        //std::cout<<t;
        auto temp = new list(t);
        int now = 0;
        for(auto j = head;j;j = j->next,now++)
        {
            if(j->next && t <= j->next->num)
            {
            	insert(head,temp,now);
            	break;
            }
            if(!j->next)
            {
            	insert(head,temp,n + i);
            	break;
           	}
        }

    }
    display(head);
    return 0;
}