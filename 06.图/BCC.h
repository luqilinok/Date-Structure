template<typename Tv, typename Te>  //基于DFS的BCC分解算法
inline void Graph<Tv, Te>::bcc(int s)
{
	reset();
	int clock = 0;
	int v = s;
	Stack<int> S;
	do
	{
		if (UNDISCOVERED == status(v))
		{
			BCC(v, clock, S);
			S.pop();
		}
	} while (s != (v = (++v%n)));

}


#define hca(x) (fTime(x))
template<typename Tv, typename Te>    //基于DFS搜索框架实现双连通域分解算法
inline void Graph<Tv, Te>::BCC(int v, int &clock, Stack<int>&S)
{
	hca(v) = dTime(v) = ++clock;
	status(v) = DISCOVERED;
	S.push(v);
	for (int u = firstNbr(v); u > -1; u = nextNbr(v, u))
	{
		switch (status(u))
		{
		case UNDISCOVERED:
			parent(u) = v;
			status(v, u) = TREE;
			BCC(u, clock, S);
			if (hca(u) < dTime(v))
			{
				hca(v) = min(hca(v), hca(u));
			}
			else
			{
				while (v != S.pop())
				{
					S.push(v);
				}
			}
			break;
		case DISCOVERED:
			status(v, u) = BACKWARD;
			if (u != parent(v))
			{
				hac(v) = min(hca(v), dTime(u));
				break;
			}

		default:
			status(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;
}

#undef hca