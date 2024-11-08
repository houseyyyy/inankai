#include <bits/stdc++.h>
class node
{
public:
	node* l,*r;
	char data;
	node(char c):data(c){l = r = NULL;}
	node(){l = r = NULL;}
	
};
void cre(node* &head,std::string pre,std::string aft)
{
	try
	{
		if(pre.size() != aft.size())
		{
			throw(head);
		}
	}
	catch(node*)
	{
		std::cerr << "error";
		exit(1);
	}

	if(pre.size() == 0)return;
	char hd = pre.front();
	int i = 0;
	for(; i < aft.size();i++)if(aft[i] == hd)break;
	head = new node(hd);	
	std::string t1,t2;
	t1 = pre.substr(1,i); t2 = pre.substr(1 + i);
	cre(head->l,t1,aft.substr(0,i));
	cre(head->r,t2,aft.substr(i + 1));
}
int gethei(node* head)
{	
	if(!head)return 0;
	int L,R,ans = 0;
	L = gethei(head->l);
	R = gethei(head->r);
	ans = std::max(L,R);
	return ans + 1;
}
int main()
{	
	int n;
	std::string pre,aft;
	std::cin >> n >> pre >> aft;
	node* head = new node;
	cre(head,pre,aft);
	std::cout<< gethei(head);
	return 0;
}