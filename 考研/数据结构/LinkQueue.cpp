#include <iostream>
using namespace std;

typedef int ElemType;
struct LinkNode
{
    ElemType data;
    struct LinkNode *next;
};
typedef struct LinkNode LinkNode;
struct LinkQueue
{
    LinkNode *front, *rear;
};
typedef struct LinkQueue LinkQueue;
typedef LinkQueue Queue;

void InitQueue(Queue &q);
bool QueueEmpty(Queue q);
void EnQueue(Queue &q, ElemType x);
bool DeQueue(Queue &q, ElemType &x);
bool GetHead(Queue q, ElemType &x);

void InitQueue(Queue &q)
{
    //使用带头节点的链表
    q.front = new LinkNode;
    q.rear = q.front;
}
bool QueueEmpty(Queue q)
{
    return q.front == q.rear;
}
void EnQueue(Queue &q, ElemType x)
{
    LinkNode *s = new LinkNode;
    s->data = x;
    s->next = NULL;
    q.rear->next = s;
    q.rear = s;
}
bool DeQueue(Queue &q, ElemType &x)
{
    if (QueueEmpty(q))
    {
        return false;
    }
    LinkNode *p = q.front->next;
    x = p->data;
    q.front->next = p->next;
    if (q.rear == p)
    {
        q.rear = q.front;
    }
    delete p;
    return true;
}
bool GetHead(Queue q, ElemType &x)
{
    if (QueueEmpty(q))
    {
        return false;
    }
    x = q.front->next->data;
    return true;
}

int main(int argc, char const *argv[])
{
    Queue q;
    ElemType x;
    InitQueue(q);
    for (size_t i = 0; i < 25; i++)
    {
        EnQueue(q, rand() % 25);
    }
    size_t count = 0;
    while (DeQueue(q, x))
    {
        printf("%2ld:%d\n", ++count, x);
    }
    return 0;
}