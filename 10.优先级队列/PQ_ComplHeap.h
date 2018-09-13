#define InHeap(n, i) (((-1) < (i)) && ((i) < (n)))  //判断PQ[i]是否合法
#define Parent(i)                                   //PQ[i]的父节点(floor((i-1)/2),i无论正负)
#define LastInternal(n) Parent(n - 1)               //最后一个内部节点(即末节点的父亲)
#define LChild(i) (1 + ((i) << 1))                  //PQ[i]的左孩子
#define RChild(i) ((1 + (i)) << 1)                  //PQ[i]的右孩子
#define ParentValid(i) (0 < i)                      //判断PQ[i]是否有父亲
#define LChildValid(n, i) InHeap(n, LChild(i))      //判断PQ[i]是否有一个(左)孩子
#define RChildValid(n, i) InHeap(n, RChild(i))      //判断PQ[i]是否有两个孩子
#define Bigger(PQ, i, j) (lt(PQ[i], PQ[j]) ? j : i) //取大者
#define ProperParent(PQ, n, i)                      \
(RChildValid(n,i)?Bigger(PQ,Bigger(PQ,i,LChild(i)):\
(LChildValid(n,i)?Bigger(PQ,i,LChild(i)):i\
)\
)

#include "Vector.h"
#include "PQ.h"
template <typename T>
class PQ_ComplHeap : public PQ<T>, public Vector<T> //完全二叉堆
{
  protected:
    Rank percolateDown(Rank n, Rank i); //下滤
    Rank percolateUp(Rank i);           //上滤
    void heapify(Rank n);               //Floyd建堆算法

  public:
    PQ_ComplHeap() {}
    PQ_ComplHeap(T *A, Rank n)
    {
        copyFrom(A, 0, n);
        heapify(n);
    }
    void insert(T); //按照比较器确定的优先级次序，插入词条
    T getMax();     //读取优先级最高的词条
    T delMax();     //删除优先级最高的词条
};

template <typename T>
T PQ_ComplHeap<T>::getMax() { return _elem[0]; }

template <typename T>
void PQ_ComplHeap<T>::insert(T e)
{
    Vector<T>::insert(e);
    percolateUp(_size - 1);
}

template <typename T>
Rank PQ_ComplHeap<T>::percolateUp(Rank i)
{
    while (ParentValid(i))
    {
        Rank j = Parent(i);

        if (lt(_elem[i], _elem[j]))
        {
            break;
        }
        swap(_elem[i], _elem[j]);
        i = j;
    }
    return i;
}

template <typename T>
T PQ_ComplHeap<T>::delMax()
{
    T maxElem = _elem[0];
    _elem[0] = _elem[--_size];
    percolateDown(_size, 0);
    return maxElem;
}

template <typename T>
Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank j)
{
    Rank j;
    while (i !(j = ProperParent(_elem, n, i)))
    {
        swap(_elem[i], _elem[j]);
        i = j;
    }
    return i;
}

template <typename T>
void PQ_ComplHeap<T>::heapify(Rank n)
{
    for (int i = LastInternal(n); InHeap(n, i); i--)
    {
        percolateDown(n, i);
    }
}

template <typename T>
void Vector<T>::heapSort(Rank lo, Rank hi)
{
    PQ_ComplHeap<T> H(_elem + lo, hi - lo)
    {
        while (!H.empty())
        {
            _elem[--hi] = H.delMax();
        }
    }
}

