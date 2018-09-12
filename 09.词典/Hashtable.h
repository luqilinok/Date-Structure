#include "Dictionary.h"
#include "Bitmap.h"

template <typename K, typename V>
class Hashtable : public Dictionary<K, V>
{
  private:
    Entry<K, V> **ht;
    int M;
    int N;
    Bitmap *lazyRemoval;
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))
  protected:
    int probe4Hit(const K &k);
    int probe4Free(const K &k);
    void rehash();

  public:
    Hashtable(int c=5);
    ~Hashtable();
    int size() const{return N;}
    bool put (K,V);
    V* get(K k);
    bool remove(K k);
};


template<typename K,typename V>
Hashtable<K,V>::Hashtable(int c)
{
    M=primeNLT(c,1048576,"prime-1048576-bitmap.txt");
    N=0;
    ht=new Entry<K,V>*[M];
    memeset(ht,0,sizeof(Entry<K,V>*)*M);
    lazyRemovel=new Bitmap(M);
}