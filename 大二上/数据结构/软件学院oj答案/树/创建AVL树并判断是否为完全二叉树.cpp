#include <bits/stdc++.h>

template <class K,class V>
class AVLnode
{
public:
	AVLnode<K,V> *left,*right,*parent;
	int bf;
	std::pair<K,V> data;
	AVLnode(const std::pair<K,V> &kv)
	{
		left = right = parent = nullptr;
		bf = 0;
		data = kv;
	}
};
template <class K,class V>
class AVLtree
{
	typedef AVLnode<K, V> Node;
public:
	Node* root;

	AVLtree(){root = nullptr;}

	bool insert(const std::pair<K,V>& kv)
	{	
		//空树直接插入
		if(!root)
		{
			root = new Node(kv);
			return true;
		}
		Node* cur = root;//当前结点要插入的位置
		Node* father = nullptr;//record cur->father
		//寻找位置并且插入
		while(cur)
		{
			father = cur;
			if(cur->data.first > kv.first)cur = cur->left;
			else if(cur->data.first < kv.first)cur = cur->right;
			else return false;
		}
		cur = new Node(kv);
		cur->parent = father;

		if(cur->data.first > father->data.first)
			father->right = cur;
		else father->left = cur;

		//调整平衡
		while(father)	
		{
			//如果在右边把父亲的平衡因子加一，代表右边层数上升
			if(cur == father->right)
				father->bf++;
			else father->bf--;
			//平衡
			if(father->bf == 0)
			{
				break;
			}
			//当前结点平衡，向上回溯，cur变father，father上移
			else if(father->bf == 1 || father->bf == -1)
			{
				cur = father;
				father = father->parent;
			}
			//当前结点不平衡，需要调整
			else if(father->bf == 2 || father->bf == -2)
			{
				if(father->bf == 2 && cur->bf == 1)//右边糖葫芦
				{
					RotateL(father);
				}
				else if(father->bf == -2 && cur->bf == -1)
				{
					RotateR(father);
				}
				else if(father->bf == 2 && cur->bf == -1)
				{
					RotateRL(father);
				}
				else if(father->bf == -2 && cur->bf == 1)
				{
					RotateLR(father);
				}
				break;

			}
			else break; 
		}
		return false;
	}
	void RotateL(Node*& father)
	{
		Node* grandparent = father->parent;
		Node* subR = father->right;
		Node* subRL = subR->left;

		father->right = subRL;

		if(subRL)
		{
			subRL->parent = father;
		}

		subR->left = father;
		father->parent = subR;

		if(grandparent == nullptr)
		{
			//根部旋转
			root = subR;
			subR->parent = nullptr;
		}
		else
		{
			if(father == grandparent->left)
				grandparent->left = subR;
			else 
				grandparent->right = subR;
			subR->parent = grandparent;
		}
		father->bf = subR->bf = 0;
	}
	void RotateR(Node*& father)
	{
		Node* grandparent = father->parent;
		Node* subL = father->left;
		Node* subLR = subL->right;

		father->left = subLR;
		if(subLR)subLR->parent = father;

		subL->right = father;
		father->parent = subL;
		if(grandparent == nullptr)
		{
			root = subL;
			subL->parent = nullptr;
		}
		else
		{
			if(father == grandparent->right)grandparent->right = subL;
			else grandparent->left = subL;
			subL->parent = grandparent;
		}
		subL->bf = father->bf = 0;
	}
	void RotateRL(Node*& father)
	{
		Node* subR = father->right;
		Node* subRL = subR->left;
		int subrl = subRL->bf;
		RotateR(subR);
		RotateL(father);
		if(subrl == 0)
		{
			subR->bf = subRL->bf = father->bf = 0;
		}
		else if(subrl == -1)
		{
			subRL->bf = father->bf = 0;
			subR->bf = 1;
		}
		else if(subrl == 1)
		{
			subRL->bf = subR->bf = 0;
			father->bf = -1;
		}
		else throw std::runtime_error("bad rotate");
	}
	void RotateLR(Node*& father)
	{
		Node* subL = father->left;
		Node* subLR = subL->right;
		int lrbf = subLR->bf;
		RotateL(subL);
		RotateR(father);
		if(lrbf == 0)
		{
			father->bf = subL->bf = subLR->bf = 0;
		}
		else if(lrbf == -1)
		{
			subL->bf = subLR->bf = 0;
			father->bf = 1;
		}
		else if(lrbf == 1)
		{
			subL->bf = -1;
			subLR->bf = father->bf = 0;
		}
		else throw std::runtime_error("bad rotate");
	}
	bool isCBT()
	{
		if(!root)return true;
		bool leaf = false;
		std::queue<Node*>q;
		q.push(root);
		while(!q.empty())
		{
			Node* t = q.front();
			q.pop();
			if((leaf && (t->left || t->right)) || (!t->left && t->right))
				return false;
			if(t->left)q.push(t->left);
			if(t->right)q.push(t->right);
			if((t->left && !t->right) || (!t->left && !t->right))
				leaf = true;
		}
		return true;
	}
};


template <class K,class V>
void mid(AVLnode<K,V>* &in)
{
	if(!in)return;
	mid(in->left);
	std::cout<< in->data.first << ' ';
	mid(in->right);
}
template <class K,class V>
void pre(AVLnode<K,V>* &in)
{
	if(!in)return;
	std::cout<< in->data.first << ' ';
	pre(in->left);
	pre(in->right);
}
template <class K,class V>
void out(const AVLtree<K,V>* in,const int n)
{
	std::queue<AVLnode<K,V>*> my;
	AVLnode<K,V>* root = in->root;
	my.push(root);
	int N = n;
	while(N)
	{
		AVLnode<K,V>* front = my.front();
		std::cout<<front->data.first <<" \n"[N == 1]; N --;
		my.pop();
		if(front->left)my.push(front->left);
		if(front->right)my.push(front->right);
	}
}
int main()
{
	int n;
	std::cin>> n;
	int* data = new int[n];
	AVLtree<int,int> *MyAvl = new AVLtree<int,int>;
	int c;
	for(int i = 0;i < n;i++)
	{
		std::cin>> c;
		MyAvl->insert({c,1});
	}
	//pre(MyAvl->root);
	//std::cout<<std::endl;
	//mid(MyAvl->root);
	//std::cout<<std::endl;
	out(MyAvl,n);
	if(MyAvl->isCBT())std::cout<<"Yes";
	else std::cout<<"No";
	delete []data;
	return 0;
}