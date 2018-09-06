template<typename T>
template<typename T>

void BinNode<T::travLevel(VST& visit)
{
    Queue<BinNodePosi(T)> Q;
    Q.enqueue(this);
    while(!Q.empty())
    {
        BinNodePosi(T) x=Q.dequeue();
        visit(x->data);
        if(HasLChild(*x))
        {
            Q.enqueue(x->lChild);
        }
        if(HasRChild(*x))
        {
            Q.enqueue(x-rChild);
        }
    }
}