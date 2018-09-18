template <typename T>
void quickSelect(Vector<T> &A, Rank k) //基于快速划分的k选取算法
{
    for (Rank lo = 0, hi = A.size() - 1; lo < hi;)
    {
        Rank i = lo;
        Rank j = hi;
        T pivot = A[lo];
        while (i < j)
        {
            while ((i < j) && (pivot <= A[j]))
            {
                j--;
                A[i] = A[j];
            }
            while ((i < j) && (A[i] <= pivot))
            {
                i++;
                A[j] = A[i];
            }
        }
        A[i] = pivot;
        if (k <= i)
        {
            hi = i - 1;
        }
        if (i <= k)
        {
            lo = i + 1;
        }
    }
}