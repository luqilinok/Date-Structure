#include"List.h"
#include"Entry.h"
#include"Quadlist.h"
#include"Dictionary"

template<typename K,typename V>

class Skiplist:public Dictionary<K,V>,public List<Quadlist<Entry<K,V>>*>
{
    protected:
        bool skipSearch(ListNode<Quadlist<Entry<K,V>>*>* &qlist,QuadlistNode<Entry<K,V>>* &p,K& k);
    public:
        int size() const{return empty()?0:last()->data->size();}
        int level(){return List::size();}
        bool put(K,V);
        V* get(K k);
        bool remove(K k);
};