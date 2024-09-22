#include <iostream>
#include <string>
#include <sstream>

class node{
public:
	node* next;
	char data;
	node(char _data):data(_data) {next = nullptr;}
	node(){next	= nullptr;}
};
void insert(node* head,node* temp)
{
	for(auto i = head;i;i = i->next)
	{
		if(!i->next)
		{
			i->next = temp;
			return;
		}
	}
}
void display(node* head)
{
	for(auto i = head->next;i;i = i->next)
	{
		std::cout<< i->data << " \n"[!i->next];
	}
}
node* merge(node* head1,node* head2)
{
	node* tail = new node;
	node* ans = tail;
	while(head1 && head2)
	{
		if(head1)
		{
			tail->next = head1;
			tail = head1;
			head1 = head1->next;
		}
		if(head2)
		{
			tail->next = head2;
			tail = head2;
			head2 = head2->next;
		}
	}
	if(head1)tail->next = head1;
	if(head2)tail->next = head2;
	
	return ans;
}
node* erase(node* head)
{
	for(auto i = head->next;i;i = i->next)
	{
		for(auto j = i->next,k = i;j;j = j->next) //k是j的上一个节点
		{
			if(j->data == i->data)
			{
				k->next = j->next;
				//删一个之后输出一遍现在长什么样子
				//display(head);
			}
			else k = k->next;
		}
	}
	return head;
}
void reverse(node* &head,const int& m,const int& n,int listNum)
{
	node* before = head,*tail = head;
	int t = 0;
	while(t <= listNum)
	{
		if(t < m - 1)before = before->next;
		if(t < n)tail = tail->next;
		t++;
	}
	node* after = tail->next;
	tail->next = nullptr;
	node* cur = before->next,*pre = nullptr; //pre存尾结点
	node* curr = cur;
	while(cur)
	{
		node*temp = cur->next;
		cur->next = pre;
		pre = cur;
		cur = temp;
	}
	before->next = pre;
	curr->next = after;
}
int main()
{
	node* headA = new node;
	node* headB = new node;

	std::string s1;
	char c;

	for(int i = 0; i < 2;i++)
	{
		getline(std::cin,s1);
		std::stringstream ss1(s1);
		while(ss1 >> c)
		{
			node*temp = new node(c);
			if(!i)insert(headA,temp);
			else insert(headB,temp);
		}
	}

	int k;
	std::cin>> k;

	display(headA);
	display(headB);
	node* headC = merge(headA->next,headB->next); // 传入第一个有数据的节点
	display(headC);
	node* headD = erase(headC);
	display(headD);

	int num = 0;

	for(auto i = headD->next;i;i = i->next)num++;
	//std::cout<< num;
	for(int i = 1;i <= num / k;i++)
	{
		reverse(headD,i * k - k + 1,i * k,num);
	}
	display(headD);
	return 0;
}