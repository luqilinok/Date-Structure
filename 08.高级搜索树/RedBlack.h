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
