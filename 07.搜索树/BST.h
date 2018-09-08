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
