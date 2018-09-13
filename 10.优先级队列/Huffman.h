HuffTree *generateTree(HuffForest *forest)
{

    while (forest->size() > 1)
    {
        HuffTree *s1 = forest->delMax();
        HuffTree *s2 = forest->delMax();
        HuffTree *s = new HuffTree();
        s->insertAsRoot(HuffChar('^', s1->root()->data.weight + s2->root()->data.weight()));
        s->attachAslC(s->root(), s1);
        s->attachAsRC(s->root(), s2);
        forest->insert(s);
    }
    HuffTree *tree = forest->delMax();
    return tree;
}