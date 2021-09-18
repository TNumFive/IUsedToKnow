#include <iostream>
using namespace std;

#define INIT_SIZE 100
#define MAX_SIZE 100
typedef int ElemType;
struct SeqList
{
    ElemType *data;
    size_t maxSize, length;
};
typedef struct SeqList SeqList;

void InitList(SeqList &l)
{
    l.length = 0;
    l.maxSize = MAX_SIZE;
    //顺序表不扩容时，初始大小应与最大容量相同
    l.data = new ElemType[INIT_SIZE];
}

size_t Length(SeqList &l)
{
    return l.length;
}
/**
 * 注意顺序表中的次序是从1开始排序的
 */
size_t LocateElem(SeqList &l, ElemType e)
{
    for (size_t i = 0; i < l.length; i++)
    {
        if (l.data[i] == e)
        {
            return i + 1;
        }
    }
    return 0;
}

bool GetElem(SeqList &l, size_t i, ElemType &e)
{
    if (i < 1 || i > l.length)
    {
        return false;
    }
    e = l.data[i - 1];
    return true;
}

bool ListInsert(SeqList &l, size_t i, ElemType e)
{
    //i = length+1 时表示在表尾插入
    if (i < 1 || i > l.length + 1)
    {
        return false;
    }
    if (l.length >= l.maxSize)
    {
        return false;
    }
    for (int j = l.length; j >= i; j--)
    {
        l.data[j] = l.data[j - 1];
    }
    l.data[i - 1] = e;
    l.length++;
    return true;
}

bool ListDelete(SeqList &l, size_t i, ElemType &e)
{
    if (i < 1 || i > l.length)
    {
        return false;
    }
    e = l.data[i - 1];
    for (size_t j = i; j < l.length; j++)
    {
        l.data[j - 1] = l.data[j];
    }
    l.length--;
    return true;
}

void PrintList(SeqList &l)
{
    for (size_t i = 0; i < l.length; i++)
    {
        cout << i + 1 << ":" << l.data[i] << endl;
    }
}

bool Empty(SeqList &l)
{
    return l.length == 0 ? true : false;
}

void DestroyList(SeqList &l)
{
    delete[] l.data;
    l.length = 0;
}

int main(int argc, char const *argv[])
{
    size_t index = 1;
    SeqList l;
    ElemType temp;
    InitList(l);
    ListInsert(l, index++, 25);
    ListInsert(l, index++, 34);
    ListInsert(l, index++, 57);
    ListInsert(l, index++, 16);
    ListInsert(l, index++, 48);
    ListInsert(l, index++, 9);
    ListInsert(l, index++, 63);
    PrintList(l);
    cout << "在位置4插入新数据50" << endl;
    ListInsert(l, 4, 50);
    PrintList(l);
    cout << "查找值为9的元素的位置:" << LocateElem(l, 9) << endl;
    cout << "查找位置2的元素的值:";
    if (GetElem(l, 2, temp))
    {
        cout << temp;
    }
    else
    {
        cout << "(指定位置不合法)";
    }
    cout << endl;
    cout << "查找位置12的元素的值:";
    if (GetElem(l, 12, temp))
    {
        cout << temp;
    }
    else
    {
        cout << "(指定位置不合法)";
    }
    cout << endl;
    cout << "删除第6个位置的数值，并输出" << endl;
    ListDelete(l, 6, temp);
    cout << 6 << ":" << temp << endl;
    PrintList(l);
    cout << "销毁顺序表" << endl;
    DestroyList(l);
    cout << "此时表" << (Empty(l) ? "为空，删除成功" : "不为空，删除失败") << endl;
    return 0;
}
