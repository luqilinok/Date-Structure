template<typename T,typename VST>   //二叉树中序遍历（迭代版1）
void traIn_I1(BinNodePosi(T) x, VST& visit)
{
	Stack<BinNodePosi(T)> S;
	while (true)
	{
		goAlongLeftBranch(x, S);
		if (S.empty())
		{
			break;
		}
		x = S.pop();
		visit(x->data);
		x = x->rChild;
	}
}


template<typename T,typename VST>  //二叉树中序遍历（迭代版2）
void traIn_I2(BinNodePosi(T) x, VST& visit)
{
	Stack<BinNodePosi(T)> S;
	while (true)
	{
		if (x)
		{
			S.push(x);
			x = x->lChild;
		}
		else if (!S.empty())
		{
			x = S.pop();
			visit(x->data);
			x = x->rChild;
		}
		else
		{
			break;
		}
	}
}