#include <iostream>
using namespace std;
typedef int ElemType;
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;
typedef LinkList List;

void InitList(List &l)
{
    l = new LNode;
}

size_t Length(List l)
{
    size_t length = 0;
    LNode *node = l->next;
    while (node != NULL)
    {
        length++;
        node = node->next;
    }
    return length;
}

LNode *GetElem(List l, size_t i)
{
    size_t j = 1;
    LNode *p = l->next;
    if (i == 0)
    {
        return l;
    }
    if (i < 1)
    {
        return NULL;
    }
    while (p && j < i)
    {
        p = p->next;
        j++;
    }
    return p;
}

LNode *LocateElem(List l, ElemType e)
{
    LNode *p = l->next;
    while (p != NULL && p->data != e)
    {
        p = p->next;
    }
    return p;
}

bool ListInsert(List l, size_t i, ElemType e)
{
    LNode *p = GetElem(l, i - 1);
    if (p == NULL)
    {
        return false;
    }
    LNode *s = new LNode;
    s->next = p->next;
    s->data = e;
    p->next = s;
    return true;
}

bool ListDelete(List l, size_t i, ElemType &e)
{
    LNode *p = GetElem(l, i - 1);
    if (p == NULL)
    {
        return false;
    }
    LNode *q = p->next;
    if (q != NULL)
    {
        p->next = q->next;
        e = q->data;
        delete q;
        return true;
    }
    else
    {
        return false;
    }
}

void PrintList(List l)
{
    LNode *p = l->next;
    while (p != NULL)
    {
        cout << p->data << endl;
        p = p->next;
    }
}

bool Empty(List l)
{
    return l->next == NULL ? true : false;
}

void DestroyList(List l)
{
    LNode *p = l->next;
    LNode *q = NULL;
    while (p != NULL)
    {
        q = p->next;
        delete p;
        p = q;
    }
    l->next = NULL;
}

int main(int argc, char const *argv[])
{
    ElemType temp = rand()%23;
    List l;
    InitList(l);
    for (size_t i = 0; i < 10; i++)
    {
        ListInsert(l, i + 1, rand()%23);
    }
    PrintList(l);
    cout << "List length: " << Length(l) << endl;
    cout << "value at 7th: " << GetElem(l, 7)->data << endl;
    cout << "delete node at 5th, ";
    if (ListDelete(l, 5, temp))
    {
        cout << "value is " << temp << ", succeeded" << endl;
    }
    else
    {
        cout << "failed" << endl;
    }
    PrintList(l);
    cout << "destroy list" << endl;
    DestroyList(l);
    cout << "is list empty: " << (Empty(l) ? "yes" : "no") << endl;
    delete l;
    return 0;
}
