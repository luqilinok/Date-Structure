#include"Graph.h"

template<typename Tv,typename Te>   //针对Dijkstra算法的顶点优先级更新器
struct DijkstraPU
{
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v)
	{
		if (g->status(v)==DISCOVERED)
		{
			if (g->priority(v)>g->priority(uk)+g->weight(uk,v))
			{
				g->priority(v) = g->priority(uk) + g->weight(uk, v);
				g->parent(v) = uk;
			}
		}
	}
};