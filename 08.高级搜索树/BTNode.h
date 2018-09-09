#include"Vector.h"
#define BTNodePosi(T) BTNode<T>*

template<typename T>
struct BTNode   //B-树节点模板类
{
	BTNodePosi(T) parent;   //父节点
	Vector<T> key;  //关联向量码
	Vector<BTNodePosi(T)> child;  //孩子向量

	BTNode() { parent = NULL; child.insert(0, NULL); }
	BTNode(T e, BTNodePosi(T) lc = NULL, BTNodePosi(T) rc = NULL)
	{
		parent = NULL;  //作为根节点，而且初始时只有一个关键码，以及两个孩子
		key.insert(0, e);
		child.insert(0, lc);
		child.insert(1, rc);
		if (lc)
		{
			lc->parent = this;
		}
		if (rc)
		{
			rc->parent = this;
		}
	}
};