template<typename T>   //二叉树的后序遍历(迭代版)
static void gotoHLVFL(Stack<BinNodePosi(T)>& S)
{
	while (BinNodePosi(T) x = S.top())
	{
		if (HasLChild(*x))
		{
			if (HasRChild(*x))
			{
				S.push(x->rChild);
			}
			S.push(x->lChild);
		}
		else
		{
			S.push(x->rChild);
		}
	}
	S.pop();
}
template<typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST& visit)
{
	Stack<BinNodePosi(T)> S;
	if (x)
	{
		S.push(x);
	}
	while (!S.empty())
	{
		if (S.top() != x->parent)
		{
			gotoHLVFL(S);
		}
		x = S.pop();
		visit(x->data);
	}
}