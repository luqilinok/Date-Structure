template <typename T>
bool majority(Vector<T> A, T &maj)  //众数查找算法:T可比较判等
{
    maj = majEleCandidate(A);  //必要性:选出候选者maj
    return majEleCheck(A, maj);  //充分性:验证maj是否的确当选
}

template <typename T>
bool majEleCheck(Vector<T> A, T maj)  //验证候选者是否确实是众数
{
    int occurrence = 0;
    for (int i = 0; i < A.size(); i++)
    {
        if (A[i] == maj)
        {
            occurrence++;
        }
        return 2 * occurrence > A.size();
    }
}

template <typename T>
T majEleCandidate(Vector<T> A)
{
    T maj;
    for (int c = 0; i = 0; i < A.size(); i++)
    {
        if (c == 0)
        {
            maj = A[i];
            c = 1;
        }
        else
        {
            maj == A[i] ? c++ : c--;
        }
    }
    return maj;
}