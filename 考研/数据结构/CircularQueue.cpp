#include <iostream>
using namespace std;

#define MAX_SIZE 25
typedef int ElemType;
struct CircularQueue
{
    ElemType data[MAX_SIZE];
    size_t front, rear;
};
typedef struct CircularQueue CircularQueue;
typedef CircularQueue Queue;

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
    //假定rear指向队尾下一个，front指向队头
    return q.front == q.rear;
}
//移动至一个位置（非队列基本操作）
size_t next(size_t &p)
{
    size_t old = p;
    p = p + 1;
    p = p % MAX_SIZE;
    return old;
}
//判断队列是否已满（非队列基本操作）
bool QueueFull(Queue q)
{
    //牺牲一个单元来区分队空和队满
    return (q.rear + 1) % MAX_SIZE == q.front;
}
bool EnQueue(Queue &q, ElemType x)
{
    if (QueueFull(q))
    {
        return false;
    }
    q.data[q.rear] = x;
    next(q.rear);
    return true;
}
bool DeQueue(Queue &q, ElemType &x)
{
    if (QueueEmpty(q))
    {
        return false;
    }
    x = q.data[q.front];
    next(q.front);
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

int main(int argc, char const *argv[])
{
    Queue q;
    ElemType x;
    InitQueue(q);
    for (size_t i = 0; i < MAX_SIZE + 1; i++)
    {
        if (!EnQueue(q, rand() % MAX_SIZE))
            break;
    }
    size_t count = 0;
    while (DeQueue(q, x))
    {
        printf("%2ld:%d\n", ++count, x);
    }
    return 0;
}