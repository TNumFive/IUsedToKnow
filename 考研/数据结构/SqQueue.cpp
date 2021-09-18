#include <iostream>
using namespace std;

#define MAX_SIZE 50
typedef int ElemType;
struct SqQueue
{
    ElemType data[MAX_SIZE];
    size_t front, rear;
};
typedef struct SqQueue SqQueue;
typedef SqQueue Queue;

void InitQueue(Queue &q);
bool QueueEmpty(Queue q);
bool EnQueue(Queue &q, ElemType x);
bool DeQueue(Queue &q, ElemType &x);
bool GetHead(Queue q, ElemType &x);

void InitQueue(Queue &q)
{
    q.front = 0;
    q.rear = 0;
}
bool QueueEmpty(Queue q)
{
    return q.front == q.rear;
}
bool EnQueue(Queue &q, ElemType x)
{
    if (q.rear == MAX_SIZE)
    {
        return false;
    }
    q.data[q.rear++] = x;
    return true;
}
bool DeQueue(Queue &q, ElemType &x)
{
    if (QueueEmpty(q))
    {
        return false;
    }
    x = q.data[q.front++];
    return true;
}
bool GetHead(Queue q, ElemType &x)
{
    if (QueueEmpty(q))
    {
        return false;
    }
    x = q.data[q.front];
    return true;
}
