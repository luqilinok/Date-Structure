#include "QuadlistNode.h"
template <typename T>
class Quadlist //Quadlist模板类
{
  private:
    int _size;                //规模
    QlistNodePosi(T) header;  //头哨兵
    QlistNodePosi(T) trailer; //尾哨兵
  protected:
    void init(); //Quadlist创建时的初始化
    int clear(); //清除所有节点
  public:
    Quadlist() { init(); } //默认构造函数
    ~Quadlist()
    {
        clear();
        delete header;
        delete trailer;
    } //删除所有节点，释放哨兵

    Rank size() const { return _size; }                     //规模
    bool empty() const { return _size <= 0; }               //判空
    QlistNodePosi(T) first() const { return header->succ; } //首节点位置
    QlistNodePosi(T) last() const { return trailer->pred; } //末节点位置
    bool valid(QlistNodePosi(T) p)                          //判断位置p是否对外合法
    {
        return p && (trailer != p)(header != p);
    }

    T remove(){QlistNodePosi(T) p};
    QlistNodePosi(T) //将*e作为p的后继，b的上邻插入
        insertAfterAbove(T const &e, QlistNodePosi(T) p, QlistNodePosi(T) b = NULL);

    void traverse(void (*)(T &));
    template <typename VST>
    void traverse(VST &);
};

template <typename T>
void Quadlist<T>::init()
{
    header = new QuadlistNode<T>;
    trailer = new QuadlistNode<T>;
    header->succ = trailer;
    header->pred = NULL;
    trailer->pred = header;
    trailer->succ = NULL;
    header->above = trailer->above = NULL;
    header->below = trailer->below = NULL;
    _size = 0;
}

template<typename T>
T Quadlist<T>::remove(QlistNodePosi(T) p)
{
    p->pred->succ=p->succ;
    p->succ->pred=p->pred;
    _size--;
    T e=p->entry;
    return e;
}

template<typename T>
int Quadlist<T>::clear()
{
    int oldSize=_size;
    while(_size>0)
    {
        remove(header->succ);
    }
    return oldSize;
}