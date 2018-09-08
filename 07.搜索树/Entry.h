template<typename K,typename V>
struct Entry  //词条模板类
{
	K key; //关键码
	V value;  //数值
	Entry(K k = K(), V v = V()) :key(k), value(v) {};
	Entry(Entry<K, V> const& e) :key(e.key), value(e.value) {};
	bool operator<(Entry<K, V> const&e) { return key < e.key; }
	bool operator>(Entry<K, V> const&e) { return key > e.key; }
	bool operator==(Entry<K, V> const&e) { return key = e.key; }
	bool operator!=(Entry<K, V> const&e) { return key != e.key; }
};