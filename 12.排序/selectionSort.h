template<typename T>
void List<T>::selectionSort(ListNodePosi(T), int n)
{
	ListNodePosi(T) head = p->pred;
	ListNodePosi(T) tail = p;
	for (int i = 0; i < n; i++)
	{
		tail = tail->succ;
	}
	while (n > 1)
	{
		ListNodePosi(T) max = selectMax(head->succ, n);
		insertBefore(tail, remove(max));
		tail = tail->pred;
		n--;
	}
}