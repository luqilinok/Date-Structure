template<typename Tv, typename Te>   //基于DFS的拓扑排序算法
inline Stack<Tv>* Graph<Tv, Te>::tSort(int s)
{
	reset();
	int clock = 0;
	int v = s;
	Stack<Tv>* S = new Stack<Tv>;
	do
	{
		if (UNDISCOVERED == status(v))
		{
			if (!TSort(v, clock, S))
			{
				while (!S->empty())
				{
					S->pop();
					break;
				}
			}
		}
	} while (s != (v = (++v%n)));
	return S;
}

template<typename Tv, typename Te>   //基于DFS的拓扑排序算法(单趟)
inline bool Graph<Tv, Te>::TSort(int v, int &clock, Stack<Tv>* S)
{
	dTime(v) = ++clock;
	status(v) = DISCOVERED;
	for (int u = firstNbr(v); u > -1; u = nextNbr(v, u))
	{
		switch (status(u))
		{
		case UNDISCOVERED:
			parent(u) = v;
			status(v, u) = Tree;
			if (!Tsort(u, clock, S))
			{
				return false;
			}
			break;
		case DISCOVERED:
			status(v, u) = BACKWARD;
			return false;
		default:
			status(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;
	S->push(vertex(v));
	return true;
}