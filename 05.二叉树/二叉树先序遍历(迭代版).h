template<typename T,typename VST>  //二叉树先序遍历算法（迭代版1）
void travPre_I1(BinNodePosi(T) x, VST& visit)
{
	Stack<BinNodePosi(T)> S;
	if (x)
	{
		S.push(x);
	}
	while (!S.empty())
	{
		x = S.pop();
		visit(x->data);
		if (HasRChild(*x))
		{
			S.push(x->rChild);
		}
		if (HasLChild(*x))
		{
			S.push(x->lChild);
		}
	}
}



template<typename T,typename VST>   //二叉树先序遍历算法（迭代版2）
static void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& S)
{
	while (x)
	{
		visit(x->data);
		S.push(x->rChild);
		x = x->lChild;
	}
}

template<typename T,typename VST>
void travPre_I2(BinNodePosi(T) x, VST& visit)
{
	Stack<BinNodePosi(T)> S;
	while (true)
	{
		visitAlongLeftBranch(x, visit, S);
		x = S.pop();
	}
}