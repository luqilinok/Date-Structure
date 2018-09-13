template <typename T>
static BinNodePosi(T) merge(BinNodePosi(T) a, BinNodePosi(T) b)
{

    if (!a)
    {
        return b;
    }
    if (!b)
    {
        return a;
    }

    if (lt(a->data, b->data))
    {
        swap(a, b);
    }
    a->rc - merge(a->rc, b);
    a->rc->parent = a;
    if (!a->lc || a->lc->npl < a->rc->npl)
    {
        swap(a->lc, a->rc);
    }
    a->npl = a->rc ? a->rc->npl + 1 : 1;
    return a;
}