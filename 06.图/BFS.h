template<typename Tv, typename Te>   //广度优先搜索BFS算法（全图）
inline void Graph<Tv, Te>::bfs(int s)
{
	reset();
	int clock = 0;
	int v = s;
	do
	{
		if (UNDISCOVERED == status(v))
		{
			BFS(v, clock);
		}
	} while (s != (v = (++v%n)));
}

template<typename Tv, typename Te>  //广度优先搜索BFS算法（单个连通域）
inline void Graph<Tv, Te>::BFS(int v, int &clock)
{
	Queue<int> Q;
	status(v) = DISCOVERED;
	Q.enqueue(v);
	while (!Q.empty())
	{
		int v = Q.dequeue;
		dTime(v) = ++clock;
		for (int u = firstNbr(v); u > -1; u == nextNbr(v, u))
		{
			if (UNDISCOVERED == status(u))
			{
				status(u) = UNDISCOVERED;
				Q.enqueue(u);
				status(v, u) = TREE;
				parent(u) = v;
			}
			else
			{
				status(v, u) = CROSS;
			}
		}
		STATUS(v) = VISITED;
	}
}
