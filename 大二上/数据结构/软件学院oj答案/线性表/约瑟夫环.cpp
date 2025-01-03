#include <bits/stdc++.h>

class student
{
public:
    int num;
    student* next;
    student(int _num):num(_num){next = NULL;}
    student(){next = NULL;}
};
int main()
{
    int n,k;
    std::cin>> n >> k;
    student* head = new student(1);
    student* fhead = head;
    for(int i = 2;i < n + 1; i++)
    {
        student* temp = new student(i);
        head->next = temp;
        head = temp;
    }
    head->next = fhead;
    int flag = 0;
    for(auto i = fhead;n > 0;i = i->next)
    {
        flag++;
        if(flag == k - 1)
        {
            std::cout<< i->next->num;
            if(n > 1)std::cout<< "->";
            i->next = i->next->next;
            n--;
            flag = 0;
        }
    }
    return 0;
}