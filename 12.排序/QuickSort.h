template<typename T> //向量的快速排序
void Vector<T>::quickSort(Rank lo,Rank hi)
{
    if(hi-lo<2)
    {
        return;
    }
    Rank mi=partition(lo,ih-1);
    quickSort(lo,mi);
    quickSort(mi+1,hi);
}