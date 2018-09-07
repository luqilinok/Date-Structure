template<typename Tv, typename Te>  //深度优先搜索DFS算法（全图）
inline void Graph<Tv, Te>::dfs(int s)
{
	reset();
	int clock = 0;
	int v = s;
	do
	{
		if (UNDISCOVERED == status(v))
		{
			DFS(v, clock);
		}
	} while (s != (v = (++v%n)));
}

template<typename Tv, typename Te>   //深度优先搜索DFS算法（单个连通域）
inline void Graph<Tv, Te>::DFS(int v, int &clock)
{
	dTime(v) = ++clock;
	status(v) = DISCOVERED;
	for (int u = firstNbr(v); u > -1; u = nextNbr(v, u))
	{
		switch (status(u))
		{
		case UNDETERMINED:
			status(v, u) = TREE;
			parent(u) = v;
			DFS(u, clock);
			break;
		case DISCOVERED:
			status(v, u) = BACKWARD;
			break;
		default:
			status(v, u) = (dTime(v) < dTime(u)) ? FORWARD : cross;
			break;
		}
	}
	status(v) = VISITED;
	fTime(v) = +clock;
}
