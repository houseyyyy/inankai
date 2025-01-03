#include <iostream>
#include <queue>
#include <string>
#include <sstream>
using namespace std;

template <class T>
class BSTree;

template <class T>
class BSTnode
{
	friend class BSTree<T>;
public:
	BSTnode(){left = right = father = nullptr;}
	BSTnode(T _val):val(_val),left(nullptr),right(nullptr),father(nullptr){}
private:
	T val;
	BSTnode<T> *left,*right,*father;
};

template <class T>
class BSTree
{
	typedef BSTnode<T> node;
public:
	BSTree():root(nullptr){}
	bool insert(T v)
	{
		if(root == nullptr)
		{
			node* temp = new node(v);
			root = temp;
			return true;
		}
		else if(this->search(v) == true)
		{
			cout<<"insert " << v << " twice" << endl;
			return false;
		}

		node* cur = root;
		node* parent = cur;//插入位置的父亲节点
		while(cur != nullptr)
		{
			parent = cur;
			if(v > cur->val)cur = cur->right;
			else cur = cur->left;
		}

		node* temp = new node(v);
		if(v > parent->val)
		{
			parent->right = temp;
			temp->father = parent;
		}
		else
		{
			parent->left = temp;
			temp->father = parent;
		}
		return true;
	}
	bool search(T v)
	{
		node* cur = root;
		while(cur != nullptr)
		{
			if(v > cur->val)cur = cur->right;
			else if(v < cur->val) cur = cur->left;
			else return true;
		}
		return false;
	}
	bool remove(T v)
	{
		if(this->search(v) == false)
		{
			cout<< v << " do not exist" <<endl;
			return false;
		}
		node* cur = root;
		node* parent = cur;//删除位置的父亲节点
		while(cur != nullptr)
		{
			if(v != cur->val)parent = cur;
			if(v > cur->val)cur = cur->right;
			else if(v < cur->val)cur = cur->left;
			else break;
		}
		if(cur->left == nullptr && cur->right == nullptr)
		{
			cur->father = nullptr;

			if(cur == root)//根节点
			{
				root = nullptr;
				return true;
			}

			if(cur == parent->left)parent->left = nullptr;
			else parent->right = nullptr;
		}
		else if(cur->left == nullptr && cur->right != nullptr)
		{
			cur->father = nullptr;
			if(cur == root)
			{
				cur->right->father = nullptr;
				root = cur->right;
				return true;
			}
			cur->right->father = parent;
			if(cur == parent->left)parent->left = cur->right;
			else parent->right = cur->right;

		}
		else if(cur->left != nullptr && cur->right == nullptr)
		{
			cur->father = nullptr;
			if(cur == root)
			{
				cur->left->father = nullptr;
				root = cur->left;
				return true;
			}
			cur->left->father = parent;
			if(cur == parent->left)parent->left = cur->left;
			else parent->right = cur->left;
		}
		else
		{
			node* l_cur = cur->left;
			node* l_parent = cur;
			while(l_cur != nullptr)
			{
				l_parent = l_cur;
				l_cur = l_cur->right;
			}
			swap(l_parent->val,cur->val);
			if(l_parent->father == cur)
			{
				cur->left = nullptr;
			}
			else 
			{
				l_parent->father->right = nullptr;
			}

		}
		return true;
	}
	void layer()
	{
		if(root == nullptr)
		{
			cout<< "error output" << endl;
			return ;
		}
		queue<node*> q;
		q.push(root);
		while(!q.empty())
		{
			node* temp = q.front();
			q.pop();
			if(temp->left != nullptr)q.push(temp->left);
			if(temp->right != nullptr)q.push(temp->right);
			cout<< temp->val << ' ';
		}
		cout<< endl;
	}
	double search_len()
	{
		double tans = 0,fans = 0;
		int tnum = 0,fnum = 0;
		if(root == nullptr)
		{
			return 0;
		}
		int lay = 1;
		int remain_node = 0;
		int flag = 0;
		queue<node*> q;
		q.push(root);
		while(!q.empty())
		{
			node* temp = q.front();
			q.pop();
			tnum ++;
			tans += lay;
			if(temp->left != nullptr)
			{
				q.push(temp->left);
				flag ++;
			}
			else fans += lay,fnum ++;
			if(temp->right != nullptr)
			{
				q.push(temp->right);
				flag ++;
			}
			else fans += lay,fnum ++;
			if(!remain_node)
			{
				lay++;
				remain_node = flag;
				flag = 0;
			}
			remain_node --;
		}
		return tans / tnum + fans / fnum;		
	}
private:
	node* root;
};

template <class T>
class AVLnode
{
public:
	AVLnode<T> *left,*right,*parent;
	int bf;
	T data;
	AVLnode(const T&kv)
	{
		left = right = parent = nullptr;
		bf = 0;
		data = kv;
	}
};

template <class T>
class AVLtree
{
	typedef AVLnode<T> Node;
public:
	Node* root;

	AVLtree(){root = nullptr;}

	bool insert(const T& kv)
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
			if(cur->data > kv)cur = cur->left;
			else if(cur->data < kv)cur = cur->right;
			else return false;
		}
		cur = new Node(kv);
		cur->parent = father;

		if(cur->data > father->data)
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

	void layer()
	{
		if(root == nullptr)
		{
			cout<< "error output" << endl;
			return ;
		}
		queue<AVLnode<T>* > q;
		q.push(root);
		while(!q.empty())
		{
			AVLnode<T>* temp = q.front();
			q.pop();
			if(temp->left != nullptr)q.push(temp->left);
			if(temp->right != nullptr)q.push(temp->right);
			cout<< temp->data << ' ';
		}
		cout<< endl;
	}
	double search_len()
	{
		double tans = 0,fans = 0;
		int tnum = 0,fnum = 0;
		if(root == nullptr)
		{
			return 0;
		}
		int lay = 1;
		int remain_node = 0;
		int flag = 0;
		queue<AVLnode<T>*> q;
		q.push(root);
		while(!q.empty())
		{
			AVLnode<T>* temp = q.front();
			q.pop();
			tnum ++;
			tans += lay;
			if(temp->left != nullptr)
			{
				q.push(temp->left);
				flag ++;
			}
			else fans += lay,fnum ++;
			if(temp->right != nullptr)
			{
				q.push(temp->right);
				flag ++;
			}
			else fans += lay,fnum ++;
			if(!remain_node)
			{
				lay++;
				remain_node = flag;
				flag = 0;
			}
			remain_node --;
		}
		return tans / tnum + fans / fnum;		
	}
};


int main()
{
	BSTree<int> t;
	AVLtree<int> a;
	string temp;
	getline(cin,temp);
	stringstream S(temp);
	while(S >> temp)
	{
		t.insert(stoi(temp));
		a.insert(stoi(temp));
	}
	t.layer();
	a.layer();
	cout<< t.search_len() - a.search_len() << endl;
	return 0;
}