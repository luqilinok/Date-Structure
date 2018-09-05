#include"BinNode.h"

template<typename T>
class BinTree
{
protected:
	int _size;
	BinNodePosi(T) _root;
	virtual int updateHeight(BinNodePosi(T) x);
	void updateHeightAbove(BinNodePosi(T) x);
public:
	BinTree() :_size(0), _root(NULL) {}
	~BinTree() { if (_size > 0)remove(_root); }
	int size() const { return _size(); }
	bool empty() const { return !_root; }
	BinNodePosi(T) root() const { return _root; }
	BinNodePosi(T) insertAsRoot(T const& e);
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &T);
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &T);
	int remove(BinNodePosi(T) x);
	BinTree<T>* secede(BinNodePosi(T) x);
	template<typename VST>
	void travLevel(VST& visit) { if (_root)_root->travLevel(visit); }
	template<typename VST>
	void travPre(VST& visit) { if (_root)_root->travPre(visit); }
	template<typename VST>
	void travIn(VST& visit) { if (_root)_root->travIn(visit); }
	template<typename VST>
	void travPost(VST& visit) { if (_root)_root->travPost(visit); }

	bool operator<(BinTree<T> const& t) { return _root && t._root&&lt(_root, t._root); }
	bool operator==(BinTree<T> const& t) { return _root && t._root && (_root == t._root); }
};

template<typename T>
inline int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + max(stature(x->lChild), stature(x->rChild));
}

template<typename T>
inline void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while (x)
	{
		updateHeight(x);
		x = x->parent;
	}
}

template<typename T>
inline BinNodePosi(T) BinTree<T>::insertAsRoot(T const & e)
{
	_size = 1;
	return _root = new BinNode<T> e;
}

template<typename T>
inline BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const & e)
{
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lChild;
}

template<typename T>
inline BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const & e)
{
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rChild;
}

template<typename T>
inline BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>*& T)
{
	if (x->lChild=T->_root)
	{
		x->lChild->parent = x;
	}
	_size += T->_size;
	updateHeightAbove(x);
	T->_root = NULL;
	T->_size = 0;
	release(T);
	T = NULL;
	return x;
}

template<typename T>
inline BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>*& T)
{
	if (x->rChild=T->_root)
	{
		x->rChild->parent = x;
	}
	_size += T->_size;
	updateHeightAbove(x);
	T->_root = NULL;
	T->_size = 0;
	release(T);
	T = NULL;
	return x;
}

template<typename T>
static int removeAt(BinNodePosi(T) x)
{
	if (!x)
	{
		return 0;
	}
	int n = 1 + removeAt(x->lChild) + removeAt(x->rChild);
	release(x->data);
	release(x);
	return n;
}

template<typename T>
inline int BinTree<T>::remove(BinNodePosi(T) x)
{
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	int n = removeAt(x);
	_size -= n;
	return n;
}

template<typename T>
inline BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)
{
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	BinTree<T>* S = new BinTree<T>;
	S->_size = x->size();
	_size -= S->_size;
	return S;
}

template<typename T,typename VST>
void travPre_R(BinNodePosi(T) x, VST& visit)  //�������
{
	if (!x)
	{
		return;
	}
	visit(x->data);
	travPre_R(x->lChild, visit);
	travPre_R(x->rChild, visit);
}

template<typename T,typename VST>
void travIn_R(BinNodePosi(T) x, VST& visit)
{
	if (x)
	{
		return;
	}
	travIn_R(x->lChild, visit);
	visit(x->data);
	travIn_R(x->rChild, visit);
}

template<typename T,typename VST>
void travPost_R(BinNodePosi(T) x, VST& visit)  //�������
{
	if (!x)
	{
		return;
	}
	travPost_R(x->lChild, visit);
	travPost_R(x->rChild, visit);
	visit(x->data);
}


