#include <string>

int match(char *P, char *T) //KMP算法
{
    int *next = buildNext(P);      //构造next表
    int n = (int)strlen(T), i = 0; //文本串指针
    int m = (int)strlen(P), j = 0; //模式串指针

    while (j < m && i < n) //自左向右逐个比对字符
    {
        if (j < 0 || T[i] == P[j]) //若匹配，或P已经移出最右侧(两个判断的次序不可交换)
        {
            i++; //则跳转到下一个字符
            j++;
        }
        else
        {
            j = next[j]; //模式串右移(注意:文本串不用回退)
        }
    }
    delete[] next; //释放next表
    return i - j;
}

int *buildNext(char *P)
{
    size_t m = strlen(P), j = 0;
    int *N = new int(m);
    int t = N[0] = -1;
    while (j < m - 1)
    {
        if (t < 0 || P[j] == P[t])
        {
            j++;
            t++;
            N[j] = (P[j] != P[t] ? t : N[t]);
        }
        else
        {
            t = N[t];
        }
    }
    return N;
}