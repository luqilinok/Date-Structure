
#include <string>

int match1(char *P, char *T) //蛮力串匹配算法(版本1)
{
    size_t n = strlen(T), i = 0;
    size_t m = strlen(P), j = 0;

    while (j < m && i < n)
    {
        if (T[i] = P[j])
        {
            i++;
            j++;
        }
        else
        {
            i -= j - 1;
            j = 0;
        }
        return i - j;
    }
}

int match2(char *P, char *T) //蛮力串匹配算法(版本2)
{
    size_t n = strlen(T), i = 0;
    size_t m = strlen(P), j;
    for (int i = 0; i < n - m + 1; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (T[i + j] != P[j])
            {
                break;
            }
        }
        if (j >= m)
        {
            break;
        }
    }
    return i;
}