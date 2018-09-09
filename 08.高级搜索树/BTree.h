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