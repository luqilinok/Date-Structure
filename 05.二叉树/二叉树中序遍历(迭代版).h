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

template<typename T, typename VST>   //二叉树中序遍历（迭代版3）
void travIn_I3(BinNodePosi(T) x, VST& visit)
{
	bool backtrack = false;
	while (true)
	{
		if (!backtrack&&HasLChild(*x))
		{
			x = x->data;
		}
		else
		{
			visit(x->data);
			if (HasRChild(*x))
			{
				x = x->rChild;
				backtrack = false;
			}
			else
			{
				if (!(x = x->succ()))
				{
					break;
				}
				backtrack = true;
			}
		}
	}
}