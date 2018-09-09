#include"BTNode.h"

template<typename T>
class BTree  //B-树模板类
{
protected:
	int _size;  //存放的关键码总数
	int _order;  //B-树的阶次，至少为3
	BTNodePosi(T) _root;  //根节点  
	BTNodePosi(T) _hot;  //search最后访问的非空的节点的位置
	void solveOverflow(BTNodePosi(T));  //因插入而上溢之后的分裂处理
	void solveUnderflow(BTNodePosi(T));  //因删除而下溢之后的合并处理
public:
	BTree(int order = 3) :_order(order), _size(0) { _root = new BTNode<T>(); }  //构造函数:默认为最低的3阶
	~BTree()  //析构函数
	{
		if (_root)
		{
			release(_root);
		}
	}
	int const order() { return _order; }  //阶次
	int const size() { return _size; }  //规模
	BTNodePosi(T)& root() { return _root; }  //树根
	bool empty()const { return !_root; }  //判空
	BTNodePosi(T) search(const T& e);  //查找
	bool insert(const T& e);  //插入
	bool remove(const T& e);  //删除
};

template<typename T>
void BTree<T>::solveOverflow(BTNodePosi(T) v)
{
	if (_order >= v->child.size())
	{
		return;
	}
	Rank s = _order / 2;
	BTNodePosi(T) u = new BTNode<T>();
	for (Rank j = 0; j < _order - s - 1; j++)
	{
		u->child.insert(j, v->child.remove(s + 1));
		u->key.insert(j, v->key.remove(s + 1));
	}
	u->child[_order - s - 1] = v->child.remove(s + 1);
	if (u->child[0])
	{
		for (Rank j = 0; j < _order - s; j++)
		{
			u->child[j]->parent = u;
		}
		BTNodePosi(T) p = v->parent;
		if (!p)
		{
			_root = p = new BTNode<T>();
			p->child[0] = v;
			v->parent = p;
		}
		Rank r = 1 + p->key.search(v->key[0]);
		p->key.insert(r, v->key.remove(s));
		p->child.insert(r + 1, u);
		u->parent = p;
		solveOverflow(p);
	}
}

template<typename T>
inline BTNodePosi(T) BTree<T>::search(const T & e)
{
	BTNodePosi(T) v = _root;
	_hot = NULL;
	while (v)
	{
		Rank r = v->key.search(e);
		if ((r >= 0) && (e == v->key(r)))
		{
			return v;
		}
		_hot = v;
		v = v->child[r + 1];
	}
	return NULL;
}

template<typename T>
inline bool BTree<T>::insert(const T & e)
{
	BTNodePosi(T) v = search(e);
	if (v)
	{
		return false;
	}
	Rank r = _hot->key.search(e);
	_hot->key.insert(r + 1, e);
	_hot->child.insert(r + 2, NULL);
	_size++;
	solveOverflow(_hot);
	return true;
}


template<typename T>
bool BTree<T>::remove(const T& e)
{
	BTNodePosi(T) v = search(e);
	if (!v)
	{
		return false;
	}
	Rank r = v->key.search(e);
	if (v->child[0])
	{
		BTNodePosi(T) u = v->child[r + 1];
		while (u->child[0])
		{
			u = u->child[0];
		}
		v->key[r] = u->key[0];
		v = u;
		r = 0;
	}
	v->key.remove(r);
	v->child.remove(r + 1);
	_size--;
	solveUnderflow(v);
	return true;
}