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

template<typename K,typename V>
V* Skiplist<K,V>::get(K k)
{
    if(empty())
    {
        return NULL;
    }
    ListNode<Quadlist<Entry<K,V>>*>* qlist=first();
    QuadlistNode<Entry<K,V>>* p=qlist->data->first();
    return skipSearch(qlist,p,k)?&(p->entry.value):NULL;
}

template<typename K,typename V>
bool Skiplist<K,V>::skipSearch(ListNode<Quadlist<Entry<K,V>>*>* &qlist,QuadlistNode<Entry<K,V>>* &p,K& k)
{
    while(true)
    {
        while(p->succ&&(p->entry.key<=k))
        {
            p=p->succ;
        }
        p=p->pred;
        if(p->pred&&(k==p->entry.key))
        {
            return true;
        }
        qlist=qlist->succ;
        if(!qlist->succ)
        {
            return false;
        }
        p=(p->pred)?p->below:qlist->data->first();
    }
}