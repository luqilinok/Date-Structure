#define IsBlack(p) (!(p)||(RB_BLACK==(p)->color))
#define IsRed(p)(!IsBlack(p))
#define BlackHeightUpdated(x)(\
    (stature((x).lChild)==stature((x).rChild))&&\
    ((x).height==(ISRed(&x)?stature((x).lChild):stature((x).lChild)+1))\
)


#include"BST"
template<typename T>
class RedBlack:public BST<T>
{
    protected:
        void solveDoubleRed(BinNodePosi(T) x);
        void solveDoubleBlack(BinNodePosi(T) x);
        int updateHeight(BinNodePosi(T) x ;

    public:
        BinNodePosi(T) insert(const T& e);
        bool remove(const T& e);
};

