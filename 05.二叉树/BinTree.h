﻿#include"BinNode.h"  
#include"Stack.h"

template<typename T>  //二叉树模板类
class BinTree
{
protected:
	int _size;  //规模
	BinNodePosi(T) _root;  //根节点
	virtual int updateHeight(BinNodePosi(T) x);  //更新节点x的高度
	void updateHeightAbove(BinNodePosi(T) x);  //更新节点x及其祖先的高度
public:
	BinTree() :_size(0), _root(NULL) {}  //构造函数
	~BinTree() { if (_size > 0)remove(_root); }  //析构函数
	int size() const { return _size(); }  //规模
	bool empty() const { return !_root; }  //判空
	BinNodePosi(T) root() const { return _root; }  //树根
	BinNodePosi(T) insertAsRoot(T const& e);  //插入根节点
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);  //e作为x的左孩子(原来没有)插入
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);  //e作为x的右孩子(原来没有)插入
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &T);  //T作为x左子树接入
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &T);  //T作为x右子树接入
	int remove(BinNodePosi(T) x);  //删除以位置x处节点为根的子树，返回该子树原先的规模
	BinTree<T>* secede(BinNodePosi(T) x);  //将子树x从当前树中删除，并将其转换为一棵独立的的子树
	
	template<typename VST>  
	void travLevel(VST& visit) { if (_root)_root->travLevel(visit); }  //层次遍历
	
	template<typename VST>
	void travPre(VST& visit) { if (_root)_root->travPre(visit); }  //先序遍历
	
	template<typename VST>
	void travIn(VST& visit) { if (_root)_root->travIn(visit); }  //中序遍历
	
	template<typename VST>
	void travPost(VST& visit) { if (_root)_root->travPost(visit); }  //后序遍历

	bool operator<(BinTree<T> const& t) { return _root && t._root&&lt(_root, t._root); }
	bool operator==(BinTree<T> const& t) { return _root && t._root && (_root == t._root); }
};

template<typename T>
inline int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + max(stature(x->lChild), stature(x->rChild));
}

template<typename T>
inline void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while (x)
	{
		updateHeight(x);
		x = x->parent;
	}
}

template<typename T>
inline BinNodePosi(T) BinTree<T>::insertAsRoot(T const & e)
{
	_size = 1;
	return _root = new BinNode<T> e;
}

template<typename T>
inline BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const & e)
{
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lChild;
}

template<typename T>
inline BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const & e)
{
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rChild;
}

template<typename T>
inline BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>*& T)
{
	if (x->lChild = T->_root)
	{
		x->lChild->parent = x;
	}
	_size += T->_size;
	updateHeightAbove(x);
	T->_root = NULL;
	T->_size = 0;
	release(T);
	T = NULL;
	return x;
}

template<typename T>
inline BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>*& T)
{
	if (x->rChild = T->_root)
	{
		x->rChild->parent = x;
	}
	_size += T->_size;
	updateHeightAbove(x);
	T->_root = NULL;
	T->_size = 0;
	release(T);
	T = NULL;
	return x;
}

template<typename T>
static int removeAt(BinNodePosi(T) x)
{
	if (!x)
	{
		return 0;
	}
	int n = 1 + removeAt(x->lChild) + removeAt(x->rChild);
	release(x->data);
	release(x);
	return n;
}

template<typename T>
inline int BinTree<T>::remove(BinNodePosi(T) x)
{
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	int n = removeAt(x);
	_size -= n;
	return n;
}

template<typename T>
inline BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)
{
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	BinTree<T>* S = new BinTree<T>;
	S->_size = x->size();
	_size -= S->_size;
	return S;
}

template<typename T, typename VST>
void travPre_R(BinNodePosi(T) x, VST& visit)  //先序遍历（递归版）
{
	if (!x)
	{
		return;
	}
	visit(x->data);
	travPre_R(x->lChild, visit);
	travPre_R(x->rChild, visit);
}

template<typename T, typename VST>   //中序遍历（递归版）
void travIn_R(BinNodePosi(T) x, VST& visit)
{
	if (x)
	{
		return;
	}
	travIn_R(x->lChild, visit);
	visit(x->data);
	travIn_R(x->rChild, visit);
}

template<typename T, typename VST>
void travPost_R(BinNodePosi(T) x, VST& visit)  //后序遍历（递归版）
{
	if (!x)
	{
		return;
	}
	travPost_R(x->lChild, visit);
	travPost_R(x->rChild, visit);
	visit(x->data);
}

template<typename T, typename VST>  //二叉树先序遍历算法（迭代版1）
void travPre_I1(BinNodePosi(T) x, VST& visit)
{
	Stack<BinNodePosi(T)> S;
	if (x)
	{
		S.push(x);
	}
	while (!S.empty())
	{
		x = S.pop();
		visit(x->data);
		if (HasRChild(*x))
		{
			S.push(x->rChild);
		}
		if (HasLChild(*x))
		{
			S.push(x->lChild);
		}
	}
}

template<typename T, typename VST>   //二叉树先序遍历算法（迭代版2）
static void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& S)
{
	while (x)
	{
		visit(x->data);
		S.push(x->rChild);
		x = x->lChild;
	}
}
template<typename T, typename VST>
void travPre_I2(BinNodePosi(T) x, VST& visit)
{
	Stack<BinNodePosi(T)> S;
	while (true)
	{
		visitAlongLeftBranch(x, visit, S);
		x = S.pop();
	}
}

template<typename T>  //二叉树中序遍历（迭代版1）
static void goAlongLeftBranch(BinNodePosi(T) x, Stack<BinNodePosi(T)>& S)
{
	while (x)
	{
		S.push(x);
		x = x->lChild;
	}
}

template<typename T, typename VST>
void traIn_I1(BinNodePosi(T) x, VST& visit)
{
	Stack<BinNodePosi(T)> S;
	while (true)
	{
		goAlongLeftBranch(x, S);
		if (S.empty())
		{
			break;
		}
		x = S.pop();
		visit(x->data);
		x = x->rChild;
	}
}

template<typename T, typename VST>  //二叉树中序遍历（迭代版2）
void traIn_I2(BinNodePosi(T) x, VST& visit)
{
	Stack<BinNodePosi(T)> S;
	while (true)
	{
		if (x)
		{
			S.push(x);
			x = x->lChild;
		}
		else if (!S.empty())
		{
			x = S.pop();
			visit(x->data);
			x = x->rChild;
		}
		else
		{
			break;
		}
	}
}

template<typename T, typename VST>   //二叉树中序遍历(迭代版3)
void travIn_I3(BinNodePosi(T) x, VST& visit)
{
	bool backtrack = false;
	while (true)
	{
		if (!backtrack&&HasLChild(*x))
		{
			x = x->data;
		}
		else
		{
			visit(x->data);
			if (HasRChild(*x))
			{
				x = x->rChild;
				backtrack = false;
			}
			else
			{
				if (!(x = x->succ()))
				{
					break;
				}
				backtrack = true;
			}
		}
	}
}

template<typename T>   //二叉树的后序遍历(迭代版)
static void gotoHLVFL(Stack<BinNodePosi(T)>& S)
{
	while (BinNodePosi(T) x = S.top())
	{
		if (HasLChild(*x))
		{
			if (HasRChild(*x))
			{
				S.push(x->rChild);
			}
			S.push(x->lChild);
		}
		else
		{
			S.push(x->rChild);
		}
	}
	S.pop();
}
template<typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST& visit)
{
	Stack<BinNodePosi(T)> S;
	if (x)
	{
		S.push(x);
	}
	while (!S.empty())
	{
		if (S.top() != x->parent)
		{
			gotoHLVFL(S);
		}
		x = S.pop();
		visit(x->data);
	}
}
