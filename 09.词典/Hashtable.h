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