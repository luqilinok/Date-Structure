template<typename T,typename VST>
void travPre_R(BinNodePosi(T) x, VST& visit)  //����������ݹ�棩
{
	if (!x)
	{
		return;
	}
	visit(x->data);
	travPre_R(x->lChild, visit);
	travPre_R(x->rChild, visit);
}