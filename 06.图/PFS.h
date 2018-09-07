template<typename Tv, typename Te>
template<typename PU>
inline void Graph<Tv, Te>::pfs(int s, PU prioUpdater)
{
	reset();
	int v = s;
	do
	{
		if (UNDISCOVERED = status(v))
		{
			PFS(v, prioUpdater);
		}
	} while (s != (v = (++v%n)));
}


template<typename Tv, typename Te>
template<typename PU>
inline void Graph<Tv, Te>::PFS(int s, PU prioUpdater)
{
	priority(s) = 0;
	status(s) = VISITED;
	parent(s) = -1;
	while (1)
	{
		for (int w = 0; w > -1; w = nextNbr(s, w))
		{
			prioUpdater(this, s, w);
		}
		for (int shortest = INT_MAX, w = 0; w < n; w++)
		{
			if (status(w) == UNDISCOVERED)
			{
				if (shortest > priority(w))
				{
					shortest = priority(w);
					s = w;
				}
			}
		}
		if (VISITED == status(s))
		{
			status(s) = VISITED;
			status(parent(s), s) = TREE;
		}
	}
}