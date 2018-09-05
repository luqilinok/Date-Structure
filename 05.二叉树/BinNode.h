﻿#include<stdlib.h>

#define IsRoot(x)(!((x).parent))
#define IsLChild(x)(!IsRoot(x)&&(&(x)==(x).parent->lChild))
#define IsRChild(x)(!IsRoot(x)&&(&(x)==(x).parent->rChild))
#define HasParent(x)(!IsRoot(x))
#define HasLChild(x)((x).lChild)
#define HasRChild(x)((x).rChild)
#define HasChild(x)(HasLChild(x)||HasRChild(x))
#define HasBothChild(x)(HasLChild(x)&&HasRChild(x))
#define IsLeaf(x)(!HasChild(x))

#define sibling(p)(\
	IsLChild(*(p))?\
		(p)->parent->rChild:\
		(p)->parent->lChild\
)

#define uncle(x)(\
	IsLChild(*((x)->parent))?\
		(x)->parent->parent->rChild:\
		(x)->parent->parent->lChild\
)

#define FromParentTo(x)(\
	IsRoot(x)?_root:(\
	IsLChild(x)?(x).parent->lChild:(x).parent->rChild\
)\
)

#define BinNodePosi(T) BinNode<T>* //节点位置
#define stature(p)((p)?(p)->height:-1) //节点亮度（与“空树高度为-1”的约定相统一）
typedef enum { RB_RED, RB_BLACK } RBColor; //节点颜色

template<typename T>struct BinNode
{
	T data;
	BinNodePosi(T) parent;
	BinNodePosi(T) lChild;
	BinNodePosi(T) rChild;

	int height;
	int npl;  //Null Path Length(左式堆，也可直接使用height代替)
	RBColor color;

	BinNode() :parent(NULL), lChild(NULL), rChild(NULL), height(0), npl(1), color(RB_RED) {}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED) :data(e), parent(p), lChild(lc), rChild(rc), height(h), npl(l), color(c) {}

	int size();
	BinNodePosi(T) insertAsLC(T const&);
	BinNodePosi(T) insertAsRC(T const&);
	BinNodePosi(T) succ();
	template<typename VST> void travLevel(VST&);
	template<typename VST> void travPre(VST&);
	template<typename VST> void travIn(VST&);
	template<typename VST> void travPost(VST&);

	bool operator<(BinNode const& bn) { return data < bn.data; }
	bool operator==(BinNode const& bn) { return data == bn.data; }
};

template<typename T>
inline BinNodePosi(T) BinNode<T>::insertAsLC(T const &e)
{
	return lChild = new BinNode(e, this);
}

template<typename T>
inline BinNodePosi(T) BinNode<T>::insertAsRC(T const &e)
{
	return rChild = new BinNode(e, this);
}

template<typename T>
template<typename VST>
inline void BinNode<T>::travIn(VST &visit)
{
	switch (rand() % 5)
	{
	case 1:
		travIn_I1(this, visit);
		break;
	case 2:
		travIn_I2(this, visit);
		break;
	case 3:
		travIn_I3(this, visit);
	case 4:
		travIn_I4(this, visit);
	default:
		travIn_R(this, visit);
		break;
	}
}
