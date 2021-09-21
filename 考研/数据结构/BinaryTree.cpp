#include <iostream>
#include <stack>
#include <queue>
#include <cstring>
using namespace std;

typedef int ElemType;
typedef struct BiTNode
{
    ElemType data;
    size_t count;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void InitBiTree(BiTree &tree)
{
    tree = new BiTNode;
    memset(tree, sizeof(BiTNode), 0);
}

void InsertNode(BiTree tree, ElemType data)
{
    BiTNode *node = tree;
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
                node->rchild = new BiTNode;
                memset(node->rchild, sizeof(BiTNode), 0);
            }
            node = node->rchild;
        }
        else
        {
            if (node->lchild == NULL)
            {
                node->lchild = new BiTNode;
                memset(node->lchild, sizeof(BiTNode), 0);
            }
            node = node->lchild;
        }
    }
}

void Visit(BiTNode *node)
{
    printf("%2d ", node->data);
}

void PreOrder(BiTree tree)
{
    if (tree != NULL)
    {
        Visit(tree);
        PreOrder(tree->lchild);
        PreOrder(tree->rchild);
    }
}

void PreOrderNoRecursion(BiTree p)
{
    stack<BiTNode *> s;
    while (p || !s.empty())
    {
        if (p)
        {
            Visit(p);
            s.push(p);
            p = p->lchild;
        }
        else
        {
            p = s.top();
            s.pop();
            p = p->rchild;
        }
    }
}

void InOrder(BiTree tree)
{
    if (tree != NULL)
    {
        InOrder(tree->lchild);
        Visit(tree);
        InOrder(tree->rchild);
    }
}

void InOrderNoRecursion(BiTree p)
{
    stack<BiTNode *> s;
    while (p || !s.empty())
    {
        if (p)
        {
            s.push(p);
            p = p->lchild;
        }
        else
        {
            p = s.top();
            s.pop();
            Visit(p);
            p = p->rchild;
        }
    }
}

void PostOrder(BiTree tree)
{
    if (tree != NULL)
    {
        PostOrder(tree->lchild);
        PostOrder(tree->rchild);
        Visit(tree);
    }
}

void PostOrderNoRecursion(BiTree p)
{
    if (!p)
    {
        //若树不存在，则无需遍历
        return;
    }
    //记录要遍历的节点
    stack<BiTNode *> s;
    //记录要遍历的节点的位置（左-1，右1，根0）
    stack<int> pos;
    //下一个要遍历的节点
    int next = -1;
    //从根节点开始
    s.push(p);
    pos.push(0);
    while (1)
    {
        if (p->lchild && next == -1)
        {
            p = p->lchild;
            s.push(p);
            pos.push(-1);
        }
        else if (p->rchild && (next == -1 || next == 1))
        {
            p = p->rchild;
            s.push(p);
            pos.push(1);
            //下一个节点尝试访问左节点
            next = -1;
        }
        else
        {
            Visit(p);
            if (pos.top() == 0)
            {
                //后续遍历，根最后输出，返回
                return;
            }
            else if (pos.top() == -1)
            {
                //该节点为左节点，尝试访问右节点
                next = 1;
            }
            else
            {
                //该节点为右节点，下一个节点是根节点
                next = 0;
            }
            s.pop();
            pos.pop();
            p = s.top();
        }
    }
}

void LevelOrder(BiTree p)
{
    if (!p)
    {
        return;
    }
    queue<BiTNode *> q;
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
}

int main(int argc, char const *argv[])
{
    BiTree tree;
    InitBiTree(tree);
    for (size_t i = 0; i < 20; i++)
    {
        InsertNode(tree, rand() % 20);
    }
    cout << "PreOrder" << endl;
    PreOrder(tree);
    cout << endl;
    cout << "PreOrderNoRecursion" << endl;
    PreOrderNoRecursion(tree);
    cout << endl;
    cout << "InOrder" << endl;
    InOrder(tree);
    cout << endl;
    cout << "InOrderNoRecursion" << endl;
    InOrderNoRecursion(tree);
    cout << endl;
    cout << "PostOrder" << endl;
    PostOrder(tree);
    cout << endl;
    cout << "PostOrderNoRecursion" << endl;
    PostOrderNoRecursion(tree);
    cout << endl;
    cout << "LevelOrder" << endl;
    LevelOrder(tree);
    cout << endl;
    return 0;
}
