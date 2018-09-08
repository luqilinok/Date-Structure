#include"BinTree.h"

template<typename T>
class BST :public BinTree<T>
{
protected:
	BinNodePosi(T) _hot;  //命中节点的父亲
	BinNodePosi(T) connect34(
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
	BinNodePosi(T) rotateAt(BinNodePosi(T) x);
public:
	virtual BinNodePosi(T)&  search(const T& e);
	virtual BinNodePosi(T) insert(const T& e);
	virtual bool remove(const T& e);
};

template<typename T>
static BinNodePosi(T) & searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot)
{
	if (!v || (e == v->data))
	{
		return v;
	}
	hot = v;
	return searchIn(((e < v->data) ? v->lChild : v->rChild), e, hot);
}

template<typename T>
BinNodePosi(T)& BST<T>::search(const T& e)
{
	return searchIn(_root, e, _hot = NULL);
}

template<typename T>
inline BinNodePosi(T) BST<T>::insert(const T & e)
{
	BinNodePosi(T) & x = search(e);
	if (x)
	{
		return x;
	}
	x = new BinNode<T>(e, _hot);
	_size++;
	updateHeightAbove(x);
	return x;
}

#include"BinTree.h"

template<typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot)
{
	BinNodePosi(T) w = x;
	BinNodePosi(T) succ = NULL;
	if (!HasLChild(*x))
	{
		succ = x->rChild;
	}
	else if (!HasRChild(*x))
	{
		succ = x->rChild;
	}
	else
	{
		w = w->succ();
		swap(x->data, w->data);
		BinNodePosi(T) u = w->parent;
		((u == x) ? u->rChild : u->rChild) = succ = w->rChild;
	}
	hot = w->parent;
	if (succ)
	{
		succ->parent = hot;
	}
	release(w->data);
	release(w);
	release succ;
}

template<typename T>
inline bool BST<T>::remove(const T & e)
{
	BinNodePosi(T) & x = search(e);
	if (!x)
	{
		return false;
	}
	removeAt(x, _hot);
	_size--;
	updateHeightAbove(_hot);
	return false;
}

template<typename T>
BinNodePosi(T) BST<T>::connect34(
	BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
	BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
)
{
	a->lChild = T0;
	if (T0)
	{
		T0->parent = a;
	}
	a->rChild = T1;
	if (T1)
	{
		T1->parent = a;
		updateHeight(a);
	}
	c->lChild = T2;
	if (T2)
	{
		T2->parent = c;
	}
	c->rChild = T3;
	if (T3)
	{
		T3->parent = c;
		updateHeight(c);
	}
	b->lChild = a;
	a->parent = b;
	b->rChild = c;
	c->parent = b;
	updateHeight(b);
	return b;
}

template<typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v)
{
	BinNodePosi(T) p = v->parent;
	BinNodePosi(T) g = p->parent;
	if (IsLChild(*p))
	{
		if (IsLChild(*v))
		{
			p->parent = g->parent;
			return connect34(v, p, g, v->lChild, v->rChild, p->rChild, g->rChild);
		}
		else
		{
			v->parent = g->parent;
			return connect34(p, v, g, v->lChild, v->rChild, g->rChild);
		}
	}
	else
	{
		if (IsRChild(*v))
		{
			p->parent = g->parent;
			return connect34(g, p, v, g->lChild, p->lChild, v->lChild, v->rChild);
		}
		else
		{
			v->parent = g->parent;
			return connect34(g, v, p, g->lChild, v->lChild, v->rChild, p->rChild);
		}
	}
}