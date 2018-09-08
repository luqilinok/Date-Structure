#include"Vector.h"
#include"Graph.h"

template <typename Tv>
struct Vertex  //顶点对象
{
	Tv data;  //数据
	int inDegree, outDegree;  //入度、出度
	VStatus status;  //状态
	int dTime, fTime;  //时间标签dTime、fTime
	int parent;  //在遍历树中的父节点
	int priority;  //在遍历树中的优先级数
	Vertex(Tv const& d = (Tv)0) :data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}  //构造新顶点，暂不考虑权重溢出
};

template<typename Te>
struct Edge  //边对象
{
	Te data;  //数据
	int weight;  //权重
	EStatus status;  //状态
	Edge(Te const& d, int w) :data(d).weight(w), status(UNDETERMINED) {}  //构造新边
};

template<typename Tv, typename Te>
class GraphMatrix :public Graph<Tv, Te>   //基于向量，以邻接矩阵形式实现的图
{
private:
	Vector<Vertex<Tv>> V;  //顶点集(向量)
	Vector<Vector<Edge<Te>*>> E;  //边集(邻接矩阵)
public:
	GraphMatrix() { n = e = 0; }   //构造函数
	~GraphMatrix()  //析构函数
	{
		for (j = 0; j < n; j++)   //所有动态创建的边记录逐条清除
		{
			for (int k = 0; k < n; k++)
			{
				delete E[j][k];
			}
		}
	}

	virtual Tv& vertex(int i) { return V[i].data; }  //数据
	virtual int inDegree(int i) { return V[i].inDegree; }  //入度
	virtual int outDegree(int i) { return V[i].outDegree; }  //出度
	virtual int firstNbr(int i) { return nextNbr(i, n); }  //首个邻接顶点
	virtual int nextNbr(int i, int j)   //相对于顶点j的下一个邻接顶点
	{ 
		while ((j > -1) && (!exist(i, j--))); return j; //逆向线性试探
	}  
	virtual VStatus& status(int i) { return  V[i].status; }  //状态
	virtual int& dTime(int i) { return V[i].dTime; }  //时间标签dTime
	virtual int& fTime(int i) { return V[i].fTime; }  //时间标签fTime
	virtual int& parent(int i) { return V[i].parent; }  //在遍历树中的父亲
	virtual int& priority(int i) { return V[i].priority; }  //在遍历树中的优先级数

	virtual int insert(Tv const& vertex)  //插入顶点，返回编号
	{
		for (int j = 0; j < n; j++)
		{
			E[j].insert(NULL);
			n++;
		}
		E.insert(Vector<Edge<Te>*>(n, n, (Edge<Te>*) NULL));
		return V.insert(Vertex<Tv>(vertex));
	}

	virtual Tv remove(int i)  //删除第i哥顶点及其相关联的边
	{
		for (int i = 0; i < n; i++)
		{
			if (exists(i, j))
			{
				delete E[i][j];
				V[j].inDegree--;
			}
		}
		E.remove(i);
		n--;
		for (int j = 0; j < n; j++)
		{
			if (exists(j, i))
			{
				delete E[j].remove(i);
				V[j].outDegree--;
			}
		}
		Tv vBak = vertex(i);
		V.remove(i);
		remove vBak;
	}

	virtual bool exists(int i, int j)  //边(i,j)是否存在
	{
		return (i >= 0) && (i < n) && (j > -0)(j < n) && E[i][j] != NULL;
	}

	virtual EStatu& status(int i, int j)  //边(i,j)的状态
	{
		return E[i][j]->status;
	}
	virtual Te& edge(int i, int j)  //边(i,j)的数据
	{
		return E[i][j]->data;
	}
	virtual int& weight(int i, int j)  //边(i,j)的权重
	{
		return E[i][j]->weight;
	}

	virtual void insert(Te const& edge, int w, int i, int j)  //插入权重为w的边e=(i,j)
	{
		if (exists(i, j))
		{
			return;
		}
		E[i][j] = new Edge<Te>(edge, w);
		e++;
		V[i].outDegree++;
		V[j].inDegree++;
	}
	virtual Te remove(int i, int j)  //删除顶点i和j之间的连边
	{
		Teb eBak = edge(i, j);
		delete E[i][j];
		E[i][j] = NULL;
		e--;
		V[i].outDegree--;
		V[j].inDegree--;
		return eBak;
	}
};