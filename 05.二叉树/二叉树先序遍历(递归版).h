template<typename T,typename VST>
void travPre_R(BinNodePosi(T) x, VST& visit)  //ÏÈÐò±éÀú£¨µÝ¹é°æ£©
{
	if (!x)
	{
		return;
	}
	visit(x->data);
	travPre_R(x->lChild, visit);
	travPre_R(x->rChild, visit);
}