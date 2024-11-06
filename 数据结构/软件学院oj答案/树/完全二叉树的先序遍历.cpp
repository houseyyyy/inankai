#include <bits/stdc++.h>

class node
{
public:
	char data;
	node *l,*r;
	node(){ l = r = nullptr;}
	node(char ch):data(ch){l = r = nullptr;}
};
void cretree(node*& head,std::string pre,int& index,int now)
{
	if(index == pre.size())return;
	head = new node(pre[index++]);
	if(now * 2 <= pre.size() - 1)
	cretree(head->l,pre,index,2 * now);
	if(now* 2 <= pre.size())
	cretree(head->r,pre,index,2 * now + 1);

}
void aft(node*head)
{
	if(!head)return;	
	aft(head->l);
	aft(head->r);
	std::cout<< head->data;
}
int main()
{
	std::string s;
	std::cin >> s;
	int index = 0,now = 1;
	node* head;
	cretree(head,s,index,now);
	aft(head);
	return 0;
}