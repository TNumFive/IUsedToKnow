#include <iostream>
using namespace std;

#define MAX_SIZE 50
typedef int ElemType;
typedef struct
{
    ElemType data[MAX_SIZE];
    size_t top;
} SqStack;
typedef SqStack Stack;

void InitStack(Stack &s);
bool StackEmpty(Stack &s);
bool Push(Stack &s, ElemType x);
bool Pop(Stack &s, ElemType &x);
bool GetTop(Stack s, ElemType &x);
void DestroyStack(Stack &s);

void InitStack(Stack &s)
{
    //栈顶指针指示当前栈顶；也可设置为0，表示栈顶指针指向下一个位置
    s.top = -1;
}
bool StackEmpty(Stack &s)
{
    if (s.top == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Push(Stack &s, ElemType x)
{
    if (s.top == MAX_SIZE - 1)
    {
        return false;
    }
    s.top++;
    s.data[s.top] = x;
    return true;
}
bool Pop(Stack &s, ElemType &x)
{
    if (s.top == -1)
    {
        return false;
    }
    x = s.data[s.top];
    s.top--;
    return true;
}
bool GetTop(Stack s, ElemType &x)
{
    if (s.top == -1)
    {
        return false;
    }
    x = s.data[s.top];
    return true;
}
void DestroyStack(Stack &s)
{
    s.top = -1;
}

int main(int argc, char const *argv[])
{
    Stack s;
    InitStack(s);
    ElemType x;
    for (size_t i = 0; i < 10; i++)
    {
        Push(s, rand() % 20);
    }
    while (!StackEmpty(s))
    {
        Pop(s, x);
        cout << x << endl;
    }

    return 0;
}
