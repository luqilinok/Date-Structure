typedef int Rank;  //秩
#define ListNodePosi(T) ListNode<T>*

template<typename T> struct ListNode  //列表节点模板类
{
	T data;  //数值
	ListNodePosi(T) pred;  //前驱
	ListNodePosi(T) succ;  //后继

	//构造函数
	ListNode() {}  //针对header和trailer的构造
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL) :data(e), pred(p), succ(s) {}  //默认构造器

	//操作接口

	ListNodePosi(T) insertAsPred(T const& e);  //紧靠当前节点之前插入新节点
	ListNodePosi(T) insertAsSucc(T const& e);  //紧靠当前节点之后插入新节点
};
template<typename T> class List
{
private:
	int _size;  //规模
	ListNodePosi(T) header;  //头哨兵
	ListNodePosi(T) trailer;  //尾哨兵

protected:
	void init();  //列表创建时的初始化
	int clear();  //清除所有节点
	void copyNodes(ListNodePosi(T), int n);  //复制列表中自位置p起的n项
	void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);  //有序列表区间归并
	void mergeSort(ListNodePosi(T)&, int);  //对从p开始连续的n个节点归并排序
	void selectionSort(ListNodePosi(T), int);  //对从p开始连续的n个节点选择排序
	void insertionSort(ListNodePosi(T), int);  //对从p开始连续的n个节点插入排序

public:
	List() { init(); }  //默认构造函数
	List(List<T> const& L);  //整体复制列表L(拷贝构造函数)
	List(List<T> const& l, Rank r, int n);  //复制列表L中自第r项起的n项
	List(ListNodePosi(T) p, int n);  //复制列表中自位置p起的n项

	~List();  //析构函数，释放所有节点

	Rank size() const { return _size; }  //规模
	bool empty() const { return _size <= 0; }  //判空
	T& operator[](Rank r) const;   //重载，支持循秩访问
	ListNodePosi(T) first() const { return header->succ; }  //首节点位置
	ListNodePosi(T) last() const { return trailer->pred; }  //末节点位置
	bool valid(ListNodePosi(T) p) //判断位置p是否对外合法
	{ 
		return p && (trailer != p) && (header != p); //将头、尾节点等同于NULL
	}  
	int disorder() const;  //判断列表是否已排序
	ListNodePosi(T) find(T const& e)const { return find(e, _size, trailer); }  //无序列表查找
	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;  //无序区间查找
	ListNodePosi(T) search(T const& e) const { return search(e, _size, trailer); }  //有序列表查找
	ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;  //有序区间查找
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);  //在p及其前n-1哥后继中选出最大者
	ListNodePosi(T) selectMax() { return selectMax(header->succ, _size); }  //整体最大者

	ListNodePosi(T) insertAsFirst(T const& e);  //将e当作首节点插入
	ListNodePosi(T) insertAsLast(T const& e);  //将e当作末节点插入
	ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const& e);  //将e当作p的前驱插入
	ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const& e);  //将e当作p的后继插入
	T remove(ListNodePosi(T) p);  //删除合法位置p出的节点，返回被删除节点
	void merge(List<T>& L) { merge(first(), size, L, L.first(), L._size); }  //全列表归并
	void sort(ListNodePosi(T) p, int n);  //列表区间排序
	void sort() { sort(first(), _size); }  //列表整体排序
	int deduplicate();  //无序去重
	int uniquify();  //有序去重
	void reverse();  //前后倒置

	void traverse(void(*T)(T&));  //遍历，依次实施visit操作(函数指针，只读或局部性修改)
	template<typename VST>  //操作器
	void traverse(VST&);  //遍历，依次实施visit操作(函数对象，可全局性修改)
};

template<typename T>
void List<T>::init()
{
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer;
	header->pred = NULL;
	trailer->pred = header;
	trailer->succ = NULL;
	_size = 0;
}

template<typename T>
int List<T>::clear()
{
	int oldSize = _size;
	while (_size > 0)
	{
		remove(header->succ);
	}
	return oldSize;
}

template<typename T>
void List<T>::copyNodes(ListNodePosi(T), int n)
{
	init();
	while (n--)
	{
		insertAsLast(p->data);
		p = p->succ;
	}
}

template<typename T>
void List<T>::merge(ListNodePosi(T)&, int n, List<T>& L, ListNodePosi(T) q, int m)
{
	ListNodePosi(T) pp = p->pred;
	while (m > 0)
	{
		if ((n > 0) && (p->data <= q->data))
		{
			if (q == (p = p->succ))
			{
				break;
			}
			n--;
		}
		else
		{
			insertBefore(p, L.remove((q = q->succ)->pred));
			m--;
		}
	}
	p = pp->succ;
}

template<typename T>
void List<T>::mergeSort(ListNodePosi(T)&, int n)
{
	if (n < 2)
	{
		return;
	}
	int m = n >> 1;
	ListNodePosi(T) q = p;
	for (int i = 0; i < m; i++)
	{
		q = q->succ;
	}
	mergeSort(p, m);
	mergeSort(q, n - m);
	merge(p, m, *this, q, n - m);
}

template<typename T>
void List<T>::selectionSort(ListNodePosi(T), int n)
{
	ListNodePosi(T) head = p->pred;
	ListNodePosi(T) tail = p;
	for (int i = 0; i < n; i++)
	{
		tail = tail->succ;
	}
	while (n > 1)
	{
		ListNodePosi(T) max = selectMax(head->succ, n);
		insertBefore(tail, remove(max));
		tail = tail->pred;
		n--;
	}
}

template<typename T>
void List<T>::insertionSort(ListNodePosi(T), int n)
{
	for (int r = 0; r < n; r++)
	{
		insertAfter(search(p->data, r, p), p->data);
		p = p->succ;
		remove(p->pred);
	}
}

template<typename T>
T & List<T>::operator[](Rank r) const
{
	ListNodePosi(T) p = first();
	while (0 < r--)
	{
		p = p->succ;
		return p->data;
	}
}

template<typename T>
ListNodePosi(T) List<T>::find(T const & e, int n, ListNodePosi(T) p) const
{
	while (0 < n--)
	{
		if (e == (p = p->pred)->data)
		{
			return p;
		}
		return NULL;
	}
}

template<typename T>
ListNodePosi(T) List<T>::search(T const & e, int n, ListNodePosi(T) p) const
{
	while (0 <= n--)
	{
		if ((p = p->pred)->date <= e)
		{
			break;
		}
	}
	return p;
}

template<typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n)
{
	ListNodePosi(T) max = p;
	for (ListNodePosi(T) cur = p; n > 1; n--)
	{
		if (!lt((cur = cur->succ)->data, max->data))
		{
			max = cur;
		}
	}
	return max;
}

template<typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const & e)
{
	_size++;
	return header->insertAsSucc(e);
}

template<typename T>
ListNodePosi(T) List<T>::insertAsLast(T const& e)
{
	_size++;
	return trailer->insertAsPred(e);
}

template<typename T>
ListNodePosi(T) List<T>::insertBefore(ListNodePosi(T) p, T const& e)
{
	_size++;
	return p->insertAsPred(e);
}

template<typename T>
ListNodePosi(T) List<T>::insertAfter(ListNodePosi(T) p, T const& e)
{
	_size++;
	return p->insertAsSucc(e);
}

template<typename T>
T List<T>::remove(ListNodePosi(T) p)
{
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;
}

template<typename T>
void List<T>::sort(ListNodePosi(T) p, int n)
{
	switch (rand() % 3)
	{
	case 1:
		insertionSort(p, n);
		break;
	case 2:
		selectionSort(p, n);
		break;
	default:
		mergeSort(p, n);
		break;
	}
}

template<typename T>
int List<T>::deduplicate()
{
	if (_size < 2)
	{
		return 0;
	}
	int oldSize = _size;
	ListNodePosi(T) p = header;
	Rank r = 0;
	while (trailer != (p = p->succ))
	{
		ListNodePosi(T) q = find(p->data, r, p);
		q ? remove(q) : r++;
	}
	return oldSize - _size;
}

template<typename T>
int List<T>::uniquify()
{
	if (_size < 2)
	{
		return 0;
	}
	int oldSize = _size;
	ListNodePosi(T) p;
	ListNodePosi(T) q;
	for (p = header; q = p->succ; trailer != q; p = q, q = q->succ)
		if (p->data == q->data)
		{
			remove(q);
			q = p;
		}
	return oldSize = _size;
}

template<typename T>
void List<T>::traverse(void(*visit)(T &))
{
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
	{
		visit(p->data);
	}
}

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e)
{
	ListNodePosi(T) x = new ListNode(e, pred, this);
	pred->succ = x;
	pred = x;
	return x;
}

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const & e)
{
	ListNodePosi(T) x = new ListNode(e, this, succ);
	succ->pred = x;
	succ = x;
	return x;
}

template<typename T>
List<T>::List(ListNodePosi(T) p, int n)
{
	copyNodes(p, n);
}

template<typename T>
List<T>::~List()
{
	clear();
	delete header;
	delete trailer;
}

template<typename T>
List<T>::List(List<T> const& L)
{
	copyNodes(L.first(), L._size);
}

template<typename T>
List<T>::List(List<T> const& L, int r, int n)
{
	copyNodes(L[r], n);
}

template<typename T>
template<typename VST>
void List<T>::traverse(VST &visit)
{
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
	{
		visit(p->data);
	}
}
