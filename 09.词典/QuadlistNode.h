#include "Entry.h"
#define QlistNodePosi(T) QuadlistNode<T> *

template <typename T>
struct QuadlistNode
{
    T entry;                //所存词条
    QlistNodePosi(T) pred;  //前驱
    QlistNodePosi(T) succ;  //后继
    QlistNodePosi(T) above; //上邻
    QlistNodePosi(T) below; //下邻
    QuadlistNode(T e = T(), QlistNodePosi(T) p = NULL, QlistNodePosi(T) s = NULL, QlistNodePosi(T) a = NULL, QlistNodePosi(T) b = NULL) : entry(e), pred(p), succ(s), above(a), below(b) {}
    QlistNodePosi(T) insertAsSuccAbove(T const &e, QlistNodePosi(T) b = NULL);
};

template<typename T>  QlistNodePosi(T)
Quadlist<T>::insertAfterAbove(T const& e,QlistNodePosi(T) p,QlistNodePosi(T) b=NULL)
{
    _size++;
    return p->insertAsSuccAbove(e,b);
}

template<typename T> QlistNodePosi(T)
QuadlistNode<T>::insertAsSuccAbove(T const& e,QlistNodePosi(T) b=NULL)
{
    QlistNodePosi(T) x=new QuadlistNode<T>(e,this,succ,NULL,b);
    succ->pred=x;
    succ=x;
    if(b)
    {
        b->above=x;
        return x;
    }
}

