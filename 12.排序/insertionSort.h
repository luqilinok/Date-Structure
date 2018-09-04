template<typename T>
void List<T>::insertionSort(ListNodePosi(T), int n)
{
	for (int r = 0; r < n; r++)
	{
		insertAfter(search(p->data, r, p), p->data);
		p = p->succ;
		remove(p->pred);
	}
}