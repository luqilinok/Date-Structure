#include"BST.h"
#include"BinTree.h"

template<typename T>
class Splay :public BST<T>  //由BST派生的
{
protected:
	BinNodePosi(T) splay(BinNodePosi(T) v);//将节点v伸展至根
public:
	BinNodePosi(T) &search(const T& e);  //查找
	BinNodePosi(T) insert(const T& e);  //插入
	bool remove(const T& e);  //删除
};

template<typename NodePosi>
inline void attachAsLChild(NodePosi p, NodePosi lc)
{
	p->lChild = lc;
	if (lc)
	{
		lc->parent = p;
	}
}

template<typename NodePosi>
inline void attachAsRChild(NodePosi p, NodePosi rc)
{
	p->rChild = rc;
	if (rc)
	{
		rc->parent = p;
	}
}

template<typename T>
BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v)  //v是因最近访问而需要伸展的节点位置
{
	if (!v)
	{
		return NULL;
	}
	BinNodePosi(T) p;  //v的父节点
	BinNodePosi(T) g;  //v的祖父节点
	while ((p = v->parent) && (g = p->parent))
	{
		BinNodePosi(T) gg = g->parent;   //每轮之后*v都以原曾祖父为父节点
		if (IsLChild(*v))
		{
			if (IsLChild(*p))
			{
				attachAsLChild(g, p->rChild);
				attachAsLChild(p, v->rChild);
				attachAsRChild(p, g);
				attachAsRChild(v, p);
			}
			else
			{
				attachAsLChild(p, v->rChild);
				attachAsRChild(g, v->lChild);
				attachAsLChild(v, g);
				attachAsRChild(v, p);
			}
		}
		else if (IsRChild(*p))
		{
			attachAsRChild(g, p->lChild);
			attachAsRChild(p, v->lChild);
			attachAsLChild(p, g);
			attachAsLChild(v, p);
		}
		else
		{
			attachAsRChild(p, v->lChild);
			attachAsLChild(g, v->rChild);
			attachAsRChild(v, g);
			attachAsLChild(v, p);
		}
		if (!gg)
		{
			v->parent = NULL;
		}
		else
		{
			(g == gg->lChild) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
		}
		updateHeight(g);
		updateHeight(p);
		updateHeight(v);
	}
	if (p = v->parent)
	{
		if (IsLChild(*v))
		{
			attachAsLChild(p, v->rChild);
			attachAsRChild(v, p);
		}
		else
		{
			attachAsRChild(p, v->lChild);
			attachAsLChild(v, p);
		}
		updateHeight(p);
		updateHeight(v);
	}
	v->parent = NULL;
	return v;
}