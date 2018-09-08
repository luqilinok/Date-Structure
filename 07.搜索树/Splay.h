#include"BST.h"

template<typename T>
class Splay :public BST<template>
{
protected:
	BinNodePosi(T) splay(BinNodePosi(T) v);
public:
	BinNodePosi(T)& search(const T& e);
	BinNodePosi(T) insert(const T& e);
	bool remove(const T& e);
};

