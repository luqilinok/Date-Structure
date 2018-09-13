#include "PQ.h"
#include "BinTree.h"

template <typename T>
class PQ_LeftHeap : public PQ<T>, public BinTree<T> //基于二叉树，以左式堆形势实现的PQ
{
  public:
    PQ_LeftHeap() {}
    PQ_LeftHeap(T *E, int n) //批量构造:可改进为Floyd建堆算法
    {
        for (int i = 0; i < n; i++)
        {
            insert(E[i]);
        }
    }
    void insert(T); //按照比较器确定的优先级次序插入元素
    T getMax();     //取出优先级最高的元素
    T delMax();     //删除优先级最高的元素
};

template <typename T>
T PQ_LeftHeap<T>::delMax()
{
    BinNodePosi(T) lHeap = _root->lc;
    BinNodePosi(T) rHeap = _root->rc;
    T e = _root->data;
    delete _root;
    _size--;
    _root = merge(lHeap, rHeap);
    if (_root)
    {
        _root->parent = NULL;
    }
    return e;
}

template<typename T>
void PQ_LeftHeap<T>::insert(T e)
{
    BinNodePosi(T) v=new BinNode<T>(e);
    _root=merge(_root,v);
    _root->parent=NULL;
    _size++;
}
