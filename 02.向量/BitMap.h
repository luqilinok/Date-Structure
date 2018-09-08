class Bitmap   //位图Bitmap类
{
private:
	char *M;   //比特图所存放的空间M[]
	int N;   //容量为N*sizeof(char)*8比特
protected:
	void init(int n)
	{
		M = new char[N = (n + 7) / 8];
		memeset(M, 0, N);
	}
public:
	Bitmap(int n = 8) { inin(n); }  //按指定规模创建比特图
	Bitmap(char* file, int n = 8)
	{
		init(n);
		FILE*fp = fopen(file, "r");
		fread(M, sizeof(char), N, fp);
		fclose(*p);
	}
	~Bitmap() { delete[] M, M = NULL; }  //析构时释放比特图空间

	void set(int k)  //插入
	{
		expand(k);
		M[k >> 3] |= (0x80 >> (k & 0x07));
	}

	void clear(int k)  //删除
	{
		expand(k);
		M[k >> 3] &= ~(0x80 >> (k & 0x07));
	}

	bool test(int k)  //测试
	{
		expand(k);
		return M[k >> 3] & (0x80 >> (k & 0x07));
	}
	void expand(int k)  //如果被访问的Bitmap[k]已出界，则需要扩容
	{
		if (k<N*8)   //仍在界内，无需扩容
		{
			return;
		}
		int oldN = N;
		char* oldM = M;
		init(2 * k);  //与向量类似的加倍策略
		memcpy_s(M, N, oldM, oldN);  //原数据转移至新空间
		delete oldM;  //释放原空间
	}
};

