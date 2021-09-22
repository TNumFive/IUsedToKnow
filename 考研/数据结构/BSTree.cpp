#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <cstring>
using namespace std;

typedef int ElemType;
typedef struct BSTNode
{
    ElemType data;
    size_t count;
    struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;

void InitBSTree(BSTree &tree)
{
    tree = new BSTNode;
    memset(tree, sizeof(BSTNode), 0);
}

void InsertBSTNode(BSTree tree, ElemType data)
{
    BSTNode *node = tree;
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
                node->rchild = new BSTNode;
                memset(node->rchild, sizeof(BSTNode), 0);
            }
            node = node->rchild;
        }
        else
        {
            if (node->lchild == NULL)
            {
                node->lchild = new BSTNode;
                memset(node->lchild, sizeof(BSTNode), 0);
            }
            node = node->lchild;
        }
    }
}

void Visit(BSTNode *node)
{
    printf("%2d ", node->data);
}

BSTNode *BSTSearch(BSTree tree, ElemType key)
{
    while (tree != NULL && tree->data != key)
    {
        if (tree->data > key)
        {
            tree = tree->rchild;
        }
        else
        {
            tree = tree->lchild;
        }
    }
    return tree;
}

void DeleteBSTNode(BSTree p, ElemType key)
{
    BSTNode *parent;
    int pos = 0;
    //找到目标节点
    while (p != NULL && p->data != key)
    {
        parent = p;
        if (p->data > key)
        {
            pos = 1;
            p = p->rchild;
        }
        else
        {
            pos = -1;
            p = p->lchild;
        }
    }
    if (p == NULL)
    {
        return;
    }
    //根据节点的孩子情况来决定子树的处理方式
    if (p->lchild && !p->rchild)
    {
        if (pos == -1)
        {
            parent->lchild = p->lchild;
        }
        else
        {
            parent->rchild = p->lchild;
        }
    }
    else if (p->rchild && !p->lchild)
    {
        if (pos == -1)
        {
            parent->lchild = p->rchild;
        }
        else
        {
            parent->rchild = p->rchild;
        }
    }
    else if (p->lchild && p->rchild)
    {
        //寻找右子树的中序遍历第一个节点及其父节点
        BSTNode *fnode = p->rchild;
        BSTNode *pfnode = p;
        while (fnode->lchild)
        {
            pfnode = fnode;
            fnode = fnode->lchild;
        }
        //左孩子查询，故第一个节点必是父节点的左孩子，且节点自身无左孩子，嫁接有孩子给父节点取代自身
        pfnode->lchild = fnode->rchild;
        //使用第一个节点去代替被删除的节点，并嫁接原节点的左右孩子
        if (pos == -1)
        {
            parent->lchild = fnode;
        }
        else
        {
            parent->rchild = fnode;
        }
        fnode->lchild = p->lchild;
        fnode->rchild = p->rchild;
    }
    //释放被删除节点
    delete p;
}

struct DisplayNode
{
    //展示的数值
    ElemType data;
    //深度
    size_t depth;
    //偏移
    size_t offset;
    //路径
    list<char> path;
};
typedef struct DisplayNode DisplayNode;

void DisplayTree(BSTree tree, const char *interval)
{
    if(tree == NULL){
        return;
    }
    list<DisplayNode> l;
    list<char> path;
    BSTNode * p = tree;
    while (p!=NULL)
    {
        
    }
       
}

int main(int argc, char const *argv[])
{
    BSTree tree;
    InitBSTree(tree);
    for (size_t i = 0; i < 50; i++)
    {
        InsertBSTNode(tree, rand() % 20);
    }
    DisplayTree(tree, "");
    return 0;
}
