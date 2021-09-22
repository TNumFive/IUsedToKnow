#include <iostream>
#include <stack>
#include <queue>
#include <cstring>
using namespace std;

typedef int ElemType;
typedef struct ThreadNode
{
    ElemType data;
    struct ThreadNode *lchild, *rchild;
    //tag:0孩子，1前驱或后继
    int ltag, rtag;
    size_t count;
} ThreadNode, *ThreadTree;

void InitThTree(ThreadTree &tree)
{
    tree = new ThreadNode;
    memset(tree, sizeof(ThreadNode), 0);
}

void InsertNode(ThreadTree tree, ElemType data)
{
    ThreadNode *node = tree;
    while (1)
    {
        if (node->count == 0)
        {
            node->data = data;
            node->count++;
            break;
        }
        if (data == node->data)
        {
            node->count++;
            break;
        }
        else if (data > node->data)
        {
            if (node->rchild == NULL)
            {
                node->rchild = new ThreadNode;
                memset(node->rchild, sizeof(ThreadNode), 0);
            }
            node = node->rchild;
        }
        else
        {
            if (node->lchild == NULL)
            {
                node->lchild = new ThreadNode;
                memset(node->lchild, sizeof(ThreadNode), 0);
            }
            node = node->lchild;
        }
    }
}

void Visit(ThreadNode *node)
{
    printf("%2d ", node->data);
}

void LevelOrder(ThreadTree p)
{
    if (!p)
    {
        return;
    }
    queue<ThreadNode *> q;
    q.push(p);
    while (!q.empty())
    {
        p = q.front();
        q.pop();
        Visit(p);
        if (p->lchild)
        {
            q.push(p->lchild);
        }
        if (p->rchild)
        {
            q.push(p->rchild);
        }
    }
    cout << endl;
}

//为何采用引用？注意CreateInThread，为了使经过遍历后的pre指向最后一个节点
void InThread(ThreadTree &p, ThreadTree &pre)
{
    if (p != NULL)
    {
        InThread(p->lchild, pre);
        if (p->lchild == NULL)
        {
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL)
        {
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;
        InThread(p->rchild, pre);
    }
}

void CreateInThread(ThreadTree tree)
{
    ThreadTree pre = NULL;
    if (tree != NULL)
    {
        InThread(tree, pre);
        pre->rchild = NULL;
        pre->rtag = 1;
    }
}

ThreadNode *FirstNode(ThreadNode *p)
{
    while (p->ltag == 0)
    {
        p = p->lchild;
    }
    return p;
}

ThreadNode *LastNode(ThreadNode *p)
{
    while (p->rtag == 0)
    {
        p = p->rchild;
    }
    return p;
}

ThreadNode *NextNode(ThreadNode *p)
{
    if (p->rtag == 0)
    {
        return FirstNode(p->rchild);
    }
    else
    {
        return p->rchild;
    }
}

ThreadNode *PreNode(ThreadNode *p)
{
    if (p->ltag == 0)
    {
        return FirstNode(p->lchild);
    }
    else
    {
        return p->lchild;
    }
}

void InOrder(ThreadTree tree)
{
    for (ThreadNode *p = FirstNode(tree); p != NULL; p = NextNode(p))
    {
        Visit(p);
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    ThreadTree tree;
    InitThTree(tree);
    cout << "InsertNode" << endl;
    for (size_t i = 0; i < 20; i++)
    {
        InsertNode(tree, rand() % 20);
    }
    cout << "LevelOrder" << endl;
    LevelOrder(tree);
    cout << "CreateInThread" << endl;
    CreateInThread(tree);
    cout << "InOrder" << endl;
    InOrder(tree);
    return 0;
}
