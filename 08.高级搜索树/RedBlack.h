#define IsBlack(p) (!(p)||(RB_BLACK==(p)->color))
#define IsRed(p)(!IsBlack(p))
#define BlackHeightUpdated(x)(\
    (stature((x).lChild)==stature((x).rChild))&&\
    ((x).height==(ISRed(&x)?stature((x).lChild):stature((x).lChild)+1))\
)

#include"BST.h"
template<typename T>
class RedBlack :public BST<T>
{
protected:
	void solveDoubleRed(BinNodePosi(T) x);  //双红修正
	void solveDoubleBlack(BinNodePosi(T) x);  //双黑修正
	int updateHeight(BinNodePosi(T) x;  //更新节点x的高度

public:
	BinNodePosi(T) insert(const T& e);  //插入
	bool remove(const T& e);  //删除
	//BST：search()等其余接口可以直接继续使用
};

template<typename T>
int RedBlack<T>::updateHeight(BinNodePosi(T) x)
{
	x->height = max(stature(x->lChild), stature(x->rChild));
	return IsBlack(x) ? x->height++ : x->height;
}

template<typename T>
BinNodePosi(T) RedBlack<T>::insert(const T& e)
{
	BinNodePosi(T) &x = search(e);
	if (x)
	{
		return x;
	}
	x = new BinNode<T>(e, _hot, NULL, NULL, -1);
	_size++;
	solveDoubleRed(x);
	return x;
}

template<typename T>
inline bool RedBlack<T>::remove(const T & e)
{
	BinNodePosi(T) &x = search(e);
	if (!x)
	{
		return false;
	}
	BinNodePosi(T) r = removeAt(x, _hot);
	if (--_size <= 0)
	{
		return true;
	}
	if (!_hot)
	{
		_root->color = RB_BLACK;
		updateHeight(_root);
		return true;
	}
	if (BlackHeightUpdated((*_hot)))
	{
		return true;
	}
	if (IsRed(r))
	{
		r->color = RB_BLACK;
		r->height++;
		return true;
	}

	solveDoubleBlack(x);
	return true;
}

/*******************************************************************************************
*  RedBlack双红调整算法：解决节点x与其父母均为红色的问题，分为两大类情况：
	  RR-1:2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
	  RR-2:3次颜色翻转，3次高度更新，0次旋转，需要递归
******************************************************************************************/

template<typename T>
void RedBlack<T>::solveDoubleRed(BinNodePosi(T) x)
{
	if (IsRoot(*x))
	{
		_root->color = RB_BLACK;
		_root->height++;
		return;
	}
	BinNodePosi(T) p = x->parent;
	if (IsBlack(p))
	{
		return;
	}
	BinNodePosi(T) g = p->parent;
	BinNodePosi(T) u = uncle(x);
	if (IsBlack(u))
	{
		if (IsLChild(*x) == IsLChild(*p))
		{
			p->color = RB_BLACK;
		}
		else
		{
			x->color = RB_BLACK;
		}
		g->color = RB_RED;

		BinNodePosi(T) gg = g->parent;
		Binnodeposi(T) f = FromParentTo(*g) = rotateAt(x);
	}
	else
	{
		p->color = RB_BLACK;
		p->height++;
		u->color = RB_BLACK;
		u->height++;
		if (!IsRoot(*g))
		{
			g->color = RB_RED;
		}
		solveDoubleRed(g);
	}
}

/*******************************************************************************************
*  RedBlack双黑调整算法:解决节点x与被其替代的节点均为黑色的问题
*  分为三大类共四种情况:
*      BB-1:2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
*      BB-2R:2次颜色翻转，2次黑高度更新，0次旋转，不再递归
*      BB-2B:1次颜色翻转，1次黑高度更新，0次旋转，需要递归
*      BB-3:2次颜色翻转，2次黑高度更新，1次旋转，转为BB-1或BB2R
******************************************************************************************/

template<typename T>
void RedBlack<T>::solveDoubleBlack(BinNodePosi(T) r)
{
	BinNodePosi(T) p = r ? r->parent : _hot;
	if (!p)
	{
		return;
	}
	BinNodePosi(T) s = (r == p->lChild) ? p->rChild : p->lChild;
	if (IsBlack(s))
	{
		BinNodePosi(T) t = NULL;
		if (HasLChild(*s) && IsRed(s->lChild))
		{
			t = s->lChild;
		}
		else if (HasRChild(*s) && IsRed(s->rChild))
		{
			t = s->rChild;
		}
		if (t)
		{
			RBColor oldColor = p->color;
			BinNodePosi(T) b = FromParentTo(*p) = rotateAt(t);
			if (HasLChild(*b))
			{
				b->lChild->color = RB_BLACK;
				updateHeight(b->lChild);
			}
			if (HasRChild(*b))
			{
				b->rChild->color = RB_BLACK;
				updateHeight(b->rChild);
			}
			b->color = oldColor;
			updateHeight(b);
		}
		else
		{
			s->color = RB_RED;
			s->height--;
			if (IsRed(p))
			{
				p->color = RB_BLACK;
			}
			else
			{
				p->height--;
				solveDoubleBlack(p);
			}
		}
		else
		{
			s->color = RB_BLACK;
			p->color = RB_RED;
			BinNodePosi(T) t = IsLChild(*s) ? s->lChild : s->rChild;
			_hot = p;
			FromParentTo(*p) = rotateAt(t);
			solveDoubleBlack(r);
		}
	}
}