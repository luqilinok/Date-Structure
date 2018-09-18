template <typename T>
T median(Vector<T> &S1, int lo1, Vector<T> &S2, int lo2, int n)
{
    if (n < 3)
    {
        return trivialMedian(S1, lo1, n, S2, lo2, n);
    }
    int mi1 = lo1 + n / 2;
    int mi2 = lo2 + (n - 1) / 2;
    if (S1[mi1] < S2[mi2])
    {
        return median(S1, mi1, S2, lo2, n + lo1 - mi1);
    }
    else if (S1[mi1] > S2[mi2])
    {
        return median(S1, lo1, S2, mi2, n + lo2 - mi2);
    }
    else
    {
        return S1[mi1];
    }
}