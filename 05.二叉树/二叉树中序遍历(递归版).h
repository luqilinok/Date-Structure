template<typename T,typename VST>   //ÖÐÐò±éÀú£¨µÝ¹é°æ£©
void travIn_R(BinNodePosi(T) x, VST& visit)
{
	if (x)
	{
		return;
	}
	travIn_R(x->lChild, visit);
	visit(x->data);
	travIn_R(x->rChild, visit);
}