#include"Stack.h"

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD };

template<typename Tv, typename Te>
class Graph  //图Graph模板类
{
private:
	void reset()  //所有顶点、边的辅助信息复位
	{
		for (int i = 0; i < n; i++)  //所有顶点的
		{
			status(i) = UNDISCOVERED;  //状态
			dTime(i) = fTime(i) = fTime(i) = -1;  //时间标签
			parent(i) = -1;  //父节点
			priority(i) = INT_MAX;  //优先级数
			for (int j = 0; j < n; j++)
			{
				if (exists（i, j）)
				{
					status(i, j) = UNDETERMINED;  //状态
				}
			}
		}
	}
	void BFS(int, int&);  //(连通域)广度优先搜索
	void DFS(int, int&);  //(连通域)深度优先搜索
	void BCC(int, int&, Stack<int>&);  //(连通域)基于DFS双连通分量分解算法
	bool TSort(int, int&, Stack<Tv>*);  //(连通域)基于DFS的拓扑排序算法
	template<typename PU>  //(连通域)优先级搜索框架
	void PFS(int PU);  //优先级搜索
public:
	int n;   //顶点总数
	virtual int insert(Tv const&) = 0;  //插入顶点，返回编号
	virtual Tv remove(int) = 0;  //删除顶点及其关联边，返回该顶点的信息
	virtual Tv& vertex(int) = 0;  //顶点v的数据(该顶点的确存在)
	virtual int inDegree(int) = 0;   //顶点v的入度(该顶点的确存在)
	virtual int outDegree(int) = 0;   //顶点v的出度(该顶点的确存在)
	virtual int firstNbr(int, int) = 0;  //顶点v的首个邻接顶点
	virtual int nextNbr(int, int) = 0;  //顶点v的(相对于顶点j的)下一邻接顶点
	virtual VStatus& status(int) = 0;   //顶点v的状态
	virtual int& dTime(int) = 0;  //顶点v的时间标签dTime
	virtual int& fTime(int) = 0;  //顶点v的时间标签fTime
	virtual int& parent(int) = 0;  //顶点v在遍历树中的父亲
	virtual int& priority(int) = 0;  //顶点v在遍历树中的优先级数

	int e;  //边总数
	virtual bool exist(int, int) = 0;  //边(v，u)是否存在
	virtual void insert(Te const&, int, int, int) = 0;   //在顶点v和u之间插入权重为w的边e
	virtual Te remove(int, int) = 0;  //删除顶点v和u之间的边e，返回该边的信息
	virtual EStatus& status(int int) = 0;  //边(v,u)的状态
	virtual Te& edge(int, int) = 0;   //边(v,u)的数据(该边确实存在)
	virtual int& weight(int, int) = 0;  //边(v,u)的权重

	void bfs(int);  //广度优先搜索
	void dfs(int);  //深度优先搜索
	void bcc(int);  //基于DFS的双连通分量的分解算法
	Stack<Tv>* tSort(int);  //基于DFS的拓扑排序算法
	void prim(int);  //最小生成树prim算法
	void dijkstra(int);  //最短路径dijkstra算法
	template<typename PU>  
	void pfs(int, PU);  //优先级搜索框架
};

template<typename Tv, typename Te>   //广度优先搜索BFS算法(全图)
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

template<typename Tv, typename Te>  //广度优先搜索BFS算法(单个连通域)
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

template<typename Tv, typename Te>
inline void Graph<Tv, Te>::bcc(int s)
{
	reset();
	int clock = 0;
	int v = s;
	Stack<int> S;
	do
	{
		if (UNDISCOVERED==status(v))
		{
			BCC(v, clock, S);
			S.pop();
		}
	} while (s!=(v=(++v%n)));

}

template<typename Tv, typename Te>   //基于DFS的拓扑排序算法
inline Stack<Tv>* Graph<Tv, Te>::tSort(int s)
{
	reset();
	int clock = 0;
	int v = s;
	Stack<Tv>* S = new Stack<Tv>;
	do
	{
		if (UNDISCOVERED==status(v))
		{
			if (!TSort(v,clock,S))
			{
				while (!S->empty())
				{
					S->pop();
					break;
				}
			}
		}
	} while (s!=(v=(++v%n)));
	return S;
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

#define hca(x) (fTime(x))
template<typename Tv, typename Te>
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
			if (hca(u)<dTime(v))
			{
				hca(v) = min(hca(v), hca(u));
			}
			else
			{
				while (v!=S.pop())
				{
					S.push(v);
				}
			}
			break;
		case DISCOVERED:
			status(v, u) = BACKWARD;
			if (u!=parent(v))
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

template<typename Tv, typename Te>   //基于DFS的拓扑排序算法(单趟)
inline bool Graph<Tv, Te>::TSort(int v, int &clock, Stack<Tv>* S)
{
	dTime(v) = ++clock;
	status(v) = DISCOVERED;
	for (int u=firstNbr(v);u>-1;u=nextNbr(v,u))
	{
		switch (status(u))
		{
		case UNDISCOVERED:
			parent(u) = v;
			status(v, u) = Tree;
			if (!Tsort(u,clock,S))
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




