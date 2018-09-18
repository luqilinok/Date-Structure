template <typename T>
T median(Vector<T> &S1, int lo1, int n1, Vector<T> &S2, int lo2, int n2)
{
    if (n1 > n2)
    {
        return median(S2, lo2, n2, S1, lo1, n1);
    }
    if (n2 < 6)
    {
        return trivialMedian(S1, lo1, n1, S2, lo2, n2);
    }
    if (2 * n1 < n2)
    {
        return median(S1, lo1, n1, S2, lo2 + (n2 - n1 - 1) / 2, n1 + 2 - (n2 - n1) % 2);
    }
    int mi1 = lo1 + n1 / 2;
    int mi2a = lo2 + (n1 - 1) / 2;
    int mi2b = lo2 + n2 - 1 - n1 / 2;
    if (S1[mi1] > S2[mi2b])
    {
        return median(S1, lo1, n1 / 2 + 1, S2, mi2a, n2 - (n1 - 1) / 2);
    }
    else if (S1[mi1] < S2[mi2a])
    {
        return median(S1, mi1, (ni + 1) / 2, S1, lo2, n2 - n1 / 2);
    }
    else
    {
        return median(S1, lo1, n1, S2, mi2a, n2 - (n1 - 1) / 2 * 2);
    }
}