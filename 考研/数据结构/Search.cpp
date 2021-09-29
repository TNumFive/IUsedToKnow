#include <iostream>

using namespace std;
#define MAX_LEN 20
typedef int ElemType;
struct SSTable
{
    ElemType *elem;
    int tableLen;
};
typedef struct SSTable SSTable;

//return 0 则查找失败
int SearchSeq(SSTable st, ElemType key)
{
    size_t i = st.tableLen;
    //将首位空间设置为0，哨兵机制，减少判断，防止溢出
    st.elem[0] = key;
    while (st.elem[i] != key)
    {
        i--;
    }
    return i;
}

int BinarySearch(SSTable st, ElemType key)
{
    int low = 0, high = st.tableLen - 1, mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (st.elem[mid] == key)
        {
            return mid;
        }
        else if (st.elem[mid] > key)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    SSTable st;
    st.elem = new ElemType[MAX_LEN];
    st.tableLen = MAX_LEN;
    cout << "Random init SeqTable" << endl;
    for (size_t i = 0; i < MAX_LEN; i++)
    {
        st.elem[i] = i + rand() % 10;
        cout << st.elem[i] << " ";
    }
    cout << endl;
    cout << "Binary Search 10" << endl;
    cout << BinarySearch(st, 10) << endl;
    delete[] st.elem;
    return 0;
}
