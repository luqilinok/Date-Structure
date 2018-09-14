#include <string>

int match(char *P, char *T) //Boyer-Morre算法(完全版，兼顾Bad Character与Good Suffix)
{
    int *bc = buildBC(P);              //构造BC表
    int *gs = buildGS(P);              //构造GS表
    size_t i = 0;                      //模式串相对于文本串的起始位置(初始时与文本串左对齐)
    while (strlen(T) >= i + strlen(P)) //不断右移(距离可能不止一个字符)模式串
    {
        int j = strlen(P) - 1;   //从模式串最末尾的字符开始
        while (P[j] == T[i + j]) //从右向左比对
        {
            if (--j < 0)
            {
                break;
            }
        }
        if (j < 0) //若极大匹配后缀==整个模式串(说明已经完全匹配)
        {
            break; //返回匹配位置
        }
        else //否则，适当地移动模式串
        {
            i += _max(gs[j], j - bc[T[i + j]];) //位移量根据BC表和GS表选择大者
        }
        delete[] gs; //销毁GS表
        delete[] bc; //销毁BC表
        return i;
    }
}