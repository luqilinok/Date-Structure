#define Balanced(x)(stature((x).lChild)==stature((x).rChild))
#define BalFac(x)(stature((x).lChild-stature((x).rChild))
#define AvlBalanced(x)((-2<BalFac(x))&&(BalFac(x)<2))
#include"BST.h"
#include"BinTree.h"


template<typename T>
class AVL :public BST<T>
{
public:
	BinNodePosi(T) insert(const T& e);
	bool remove(const T& e);
};


/******************************************************************************************
* 在左、右孩子中取更高者，
* 在AVL平衡调整前，借此确定重构方案
******************************************************************************************/
#define tallerChild(x)(\
stature((x)->lChild)>stature((x)->rChild)?(x)->lChild:(\
stature((x)->rChild)>stature((x)->lChild)?(x)->lChild:(\
IsLChild(*(x))?(x)->lChild:(x)->rChild\
)\
)\
)

template<typename T>
inline BinNodePosi(T) AVL<T>::insert(const T & e)
{
	BinNodePosi(T)& x = search(e);
	if (x)
	{
		return x;
	}
	BinNodePosi(T) xx = x = new BinNode<T>(e, _hot);
	_size++;

	for (BinNodePosi(T) g = _hot; g; g = g->parent)
	{
		if (!AvlBalanced(*g))
		{
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
			break;
		}
		else
		{
			updateHeight(g);
		}
	}
	return xx;
}

template<typename T>
inline bool AVL<T>::remove(const T & e)
{
	BinNodePosi(T)& x = search(e);
	if (!x)
	{
		return false;
	}
	removeAt(x, _hot);
	_size--;
	for (BinNodePosi(T) g = _hot; g; g = g->parent)
	{
		if (!AvlBalanced(*g))
		{
			g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
		}
		updateHeight(g);
	}
	return true;
}
