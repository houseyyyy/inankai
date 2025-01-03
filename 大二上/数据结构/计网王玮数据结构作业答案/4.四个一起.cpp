#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>
#include <cmath>
#include <set>
using namespace std;


class node
{
public:
	static int num;
	node* left,*right;
	string data;
	node(string t):data(t){left = right = nullptr;}
	node(){left = right = nullptr;}
};

int node::num = 0;

//返回二叉树中编号是t的结点的指针，从0开始的下标
node* find(node* root,int t)
{
	int i = 0;
	queue<node*> q;
	q.push(root);
	while(i < root->num)
	{
		node* fro = q.front();
		q.pop();
		if(2 * i + 1 < root->num)q.push(fro->left);
		if(2 * i + 2 < root->num)q.push(fro->right);
		if(i == t)
		{
			return fro;
		}
		i++;

	}
}

void build_tree(string& in,node* root)
{
	stringstream S(in);
	string temp;
	vector<string> v;
	while(S >> temp)v.push_back(temp);
	root->num = v.size();
	int t = 0;
	queue<node*> q;
	q.push(root);
	while(t < v.size())
	{
		node* fro = q.front();
		q.pop();
		fro->data = v[t];
		if(2*t + 1 < v.size())
		{
			fro->left = new node;
			q.push(fro->left);
		}
		if(2*t + 2 < v.size())
		{	
			fro->right = new node;
			q.push(fro->right);
		}
		t++;
	}
}

//删除第k层结点
void erase(node*& root,int k)
{
	//判断删除层数是不是合法的
	if(k < 0 || k > log2(root->num + 1))
	{
		cerr<<"Layer k does not exist.\nplease input again";
		exit(1);
	}

	//删除根节点单独处理
	if(k == 1)
	{
		node* maxleft = root->right;
		node* maxleft_parent = root;
		while(maxleft && maxleft->data != "null")
		{
			maxleft_parent = maxleft;
			maxleft = maxleft->left;
		}
		maxleft_parent->left = root->left;
		root = root->right;//更新根节点
		return;
	}

	queue<node*> q;
	q.push(root);
	int t = 0;
	while(t < root->num)
	{
		node* fro = q.front();
		q.pop();

		if(2*t + 1 < root->num)q.push(fro->left);
		if(2*t + 2 < root->num)q.push(fro->right);

		//判断是不是第k层
		if(t <= pow(2,k) - 2 && t >= pow(2,k - 1) - 1)
		{
			//叶子
			if((!fro->left || fro->left->data == "null") && (!fro->right || fro->right->data == "null"))
			{
				fro->data = "null";
			}
			//只有左
			else if((fro->left && fro->left->data != "null") && (!fro->right || fro->right->data == "null"))
			{
				//parent 是要删除结点fro的父亲结点(这里有bug删除第1层会出问题，单独处理删除结点)
				node* parent = find(root,(t + 1) / 2 - 1);
				//判断连左还是连右
				if(fro == parent->left)parent->left = fro->left;
				if(fro == parent->right)parent->right = fro->right;
			}
			//只有右
			else if((fro->right && fro->right->data != "null") && (!fro->left || fro->left->data == "null"))
			{
				node* parent = find(root,(t + 1) / 2 - 1);
				if(fro == parent->left)parent->left = fro->left;
				if(fro == parent->right)parent->right = fro->right;
			}
			//左右都有
			//原来位置接右节点，左节点接到右节点中序遍历第一个(最左下角的)
			else if((fro->right && fro->right->data != "null") && (fro->left && fro->left->data != "null") )
			{
				node* parent = find(root,(t + 1) / 2 - 1);
				if(fro == parent->left)parent->left = fro->right;
				if(fro == parent->right)parent->right = fro->right;
				//找到最左下的结点 leftparent 表示最左下的结点，因为while最后一次成立的时候maxleft已经到最左下的左孩子了
				//用leftparent记录它的父亲
				node* maxleft = fro->right;
				node* leftparent = fro;
				while(maxleft->left && maxleft->data != "null")
				{	
					leftparent = maxleft;
					maxleft = maxleft->left;

				}
				leftparent->left = fro->left;
			}
			else 
			{
				cerr << "erase error";
				exit(1);
			}
		}
		t++;
	}

}
void dfs(int cur,int n,bool*& isadd,bool*& ans,int k,int& now)
{
	//越界，不是可选解,或者结点已经搜索到
	if(cur < 0 || n <= cur || isadd[cur])
	{
		return;
	}
	if(now == k)
	{
		ans[cur] = true;
		return;
	}
	//标记当前结点表示已经找到
	isadd[cur] = true;
	//父亲结点
	now ++;
	dfs((cur + 1) / 2 - 1,n,isadd,ans,k,now);
	now--;
	//左
	now++;
	dfs((cur + 1) * 2 - 1,n,isadd,ans,k,now);
	now--;
	//右
	now++;
	dfs((cur + 1) * 2,n,isadd,ans,k,now);
	now--;
	//还原
	isadd[cur] = false;
}
//寻找和值为value距离为k的结点集合
void find_distance(string in,string value,int k)
{
	//构造层序数组
	stringstream S(in);
	string temp;
	vector<string> v;
	while(S >> temp)v.push_back(temp);
	bool* isadd = new bool[v.size()];
	bool* ans = new bool[v.size()];
	for(int i = 0; i < v.size();i++)ans[i] = false;
	
	for(int i = 0; i < v.size();i++)
	{
		if(v[i] == value)
		{
			//寻找距离为k的结点,有点类似dfs
			for(int i = 0; i < v.size();i++)isadd[i] = false;
			int now = 0;
			dfs(i,v.size(),isadd,ans,k,now);


		}
	}			
	for(int i = 0; i < v.size();i++)
	{
		if(ans[i])
		{
			if(v[i] != "null")cout<< v[i] << ' ';
		}
	}
}
void pre(node* root)
{
	if(!root || root->data == "null")return;
	cout<<root->data;
	pre(root->left);
	pre(root->right);
}
void mid(node* root)
{
	if(!root || root->data == "null")return;
	mid(root->left);
	cout<<root->data;
	mid(root->right);	
}
void ceng(node* root)
{
	queue<node*> q;
	q.push(root);
	while(!q.empty())
	{
		node* fro = q.front();
		q.pop();
		cout<< fro->data;
		if(fro->left && fro->left->data != "null")q.push(fro->left);
		if(fro->right && fro->right->data != "null")q.push(fro->right);
	}
}
vector<string> sub(vector<string> a,int sta,int en)
{
	vector<string> ans;
	for(int i = 0; i < a.size();i++)
	{
		if(i >= sta && i < en)ans.push_back(a[i]);
	}
	return ans;
}
void cre(node*& root,vector<string> a,vector<string> b)
{
	try
	{
		if(a.size() != b.size())
		{
			throw(root);
		}
	}
	catch(node*)
	{
		cerr << "error";
		exit(1);
	}
	if(a.size() == 0)return;
	string hd = a.front();
	int i = 0;
	for(; i < a.size();i++)if(b[i] == hd)break;
	root = new node(hd);
	cre(root->left,sub(a,1,i + 1),sub(b,0,i));
	cre(root->right,sub(a,1 + i,a.size()),sub(b,1 + i,b.size()));
}
int main()
{	
	string in;
	cin >> in;
	for(int i = 0; i < in.size();i++)
	{
		if(in[i] == '[' || in[i] == ']' || in[i] == ',')in[i] = ' ';
	}
	node* root = new node;
	build_tree(in,root);

	string k;
	int dis;
	cout<<"pre:";
	pre(root);cout<<endl;
	cout<<"mid:";
	mid(root);cout<<endl;
	cout<<"ceng:";
	ceng(root);cout<<endl;
	cout<< "input value and distance" << endl;
	cin>> k >> dis;
	cout<< "the answer is:" << endl;
	find_distance(in,k,dis);
	cout<<endl;



	//删除第t层
	int t;
	cout<< "input the layer to delete";
	cin>> t;
	erase(root,t);
	cout<< endl << "the tree have erased " << t << " layer" << endl;
	cout<<"pre:";
	pre(root);cout<<endl;
	cout<<"mid:";
	mid(root);cout<<endl;
	cout<<"ceng:";
	ceng(root);cout<<endl;

	cout<< "input preorder and inorder" << endl;
	vector<string> a,b;


	string temp;
	getline(cin,temp);getline(cin,temp);//bug
	stringstream Sa(temp);
	string tempstring;
	while(Sa >> tempstring)a.push_back(tempstring);
	//cout<< a.size();
	getline(cin,temp);
	stringstream Sb(temp);
	while(Sb >> tempstring)b.push_back(tempstring);
	for(auto c:a)cout<< c;
	for(auto c:b)cout<< c;
		cout <<endl;
	node* seroot = new node;
	cre(seroot,a,b);
	cout<<"pre:";
	pre(seroot);cout<<endl;
	cout<<"mid:";
	mid(seroot);cout<<endl;
	cout<<"ceng:";
	ceng(seroot);cout<<endl;
	return 0;
}