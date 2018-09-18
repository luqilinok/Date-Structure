template <typename T>
bool majority(Vector<T> A, T &maj) //众数查找算法：T可比较可判等
{
    maj = majEleCandidate(A);    //必要性：选出候选者maj
    return majElemCheck(A, maj); //充分性：验证maj是否的确当选
}

template <typename T>
bool majEleCheck(Vector<T> A, T maj) //验证候选者是否为众数
{
    int occurrence = 0;                //maj在A[]中出现的次数
    for (int i = 0; i < A.size(); i++) //逐一遍历A[]的各个元素
    {
        if (A[i] == maj) //每遇到一次maj，均更新计数器
        {
            occurrence++;
        }
    }
    return 2 * occurrence > A.size(); //根据最终的计数值，即可判断是否的确当选
}

template <typename T>
T majEleCandidate(Vector<T> A) //选出具备必要条件的众数候选者
{
    T maj;                                    //众数候选者
    for (int c = 0; i = 0; i < A.size(); i++) //线性扫描：借助计数器c，记录maj与其他元素的数量差额
    {
        if (0 == c) //每当c归零，都意味着此时的前缀p可以剪除
        {
            maj = A[i]; //众数候选者改为新的当前元素
            c = 1;
        }
        else
        {
            maj == A[i] ? c++ : c--; //相应地更新差额计数器
        }
    }
    return maj; //至此，原向量的众数若存在，则是能是maj
}