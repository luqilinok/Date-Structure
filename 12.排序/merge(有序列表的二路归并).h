template<typename T>
void List<T>::merge(ListNodePosi(T)&, int n, List<T>& L, ListNodePosi(T) q, int m)
{
	ListNodePosi(T) pp = p->pred;
	while (m > 0)
	{
		if ((n > 0) && (p->data <= q->data))
		{
			if (q == (p = p->succ))
			{
				break;
			}
			n--;
		}
		else
		{
			insertBefore(p, L.remove((q = q->succ)->pred));
			m--;
		}
	}
	p = pp->succ;
}