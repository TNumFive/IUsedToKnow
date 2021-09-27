#include <iostream>
#include <cstring>
#include <queue>
#include <list>
using namespace std;

#define MAX_VERTEX_NUM 10
#define EDGE_TYPE_MAX INT32_MAX
typedef int VertexType;
typedef int EdgeType;
//采用无压缩邻接矩阵，经修改，此处图操作即算法针对无向图
typedef struct
{
    //简单使用对应需要里的节点值不为0代表该节点存在，简化判断
    VertexType vertex[MAX_VERTEX_NUM];
    //0表示无限，>0表示权
    EdgeType edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    size_t vexNum, arcNum;
} Graph;
bool Adjacent(Graph &g, VertexType x, VertexType y)
{
    if (x < 0 || y < 0 || x >= MAX_VERTEX_NUM || y >= MAX_VERTEX_NUM)
    {
        return false;
    }
    //由于无向，只做一边的判断
    if (g.edge[x][y] > 0)
    {
        return true;
    }
    return false;
}
list<VertexType> Neighbors(Graph &g, VertexType x)
{
    list<VertexType> l;
    if (x < 0 || x >= MAX_VERTEX_NUM)
    {
        return l;
    }
    for (size_t i = 0; i < MAX_VERTEX_NUM; i++)
    {
        if (g.edge[x][i] > 0)
        {
            l.push_back(i);
        }
    }
    return l;
}
bool InsertVertex(Graph &g, VertexType x)
{
    if (x < 0 || x >= MAX_VERTEX_NUM)
    {
        return false;
    }
    if (g.vertex[x] == 0)
    {
        g.vexNum++;
        g.vertex[x] = 1;
    }
    return true;
}
bool DeleteVertex(Graph &g, VertexType x)
{
    if (x < 0 || x >= MAX_VERTEX_NUM)
    {
        return false;
    }
    if (g.vertex[x] > 0)
    {
        g.vexNum--;
        g.vertex[x] = 0;
    }
    //去边
    for (size_t i = 0; i < MAX_VERTEX_NUM; i++)
    {
        if (g.edge[i][x] > 0)
        {
            g.edge[i][x] = 0;
            g.edge[x][i] = 0;
            g.arcNum--;
        }
    }
    return true;
}
bool AddEdge(Graph &g, VertexType x, VertexType y)
{
    if (x < 0 || y < 0 || x >= MAX_VERTEX_NUM || y >= MAX_VERTEX_NUM)
    {
        return false;
    }
    if (g.vertex[x] == 0 || g.vertex[y] == 0)
    {
        return false;
    }
    if (g.edge[x][y] == 0)
    {
        g.edge[x][y] = 1;
        g.edge[y][x] = 1;
        g.arcNum++;
    }
    return true;
}
bool RemoveEdge(Graph &g, VertexType x, VertexType y)
{
    if (x < 0 || y < 0 || x >= MAX_VERTEX_NUM || y >= MAX_VERTEX_NUM)
    {
        return false;
    }
    if (g.edge[x][y] > 0)
    {
        g.edge[x][y] = 0;
        g.edge[y][x] = 0;
        g.arcNum--;
    }
    return true;
}
VertexType FirstNeighbor(Graph &g, VertexType x)
{
    if (x < 0 || x >= MAX_VERTEX_NUM)
    {
        return -1;
    }
    for (size_t i = 0; i < MAX_VERTEX_NUM; i++)
    {
        if (g.edge[x][i] > 0)
        {
            return i;
        }
    }
    return -1;
}
VertexType NextNeighbor(Graph &g, VertexType x, VertexType y)
{
    if (x < 0 || y < 0 || x >= MAX_VERTEX_NUM || y >= MAX_VERTEX_NUM)
    {
        return -1;
    }
    for (size_t i = y + 1; i < MAX_VERTEX_NUM; i++)
    {
        if (g.edge[x][i] > 0)
        {
            return i;
        }
    }
    return -1;
}
EdgeType GetEdgeValue(Graph &g, VertexType x, VertexType y)
{
    if (x < 0 || y < 0 || x >= MAX_VERTEX_NUM || y >= MAX_VERTEX_NUM)
    {
        return -1;
    }
    return g.edge[x][y];
}
bool SetEdgeValue(Graph &g, VertexType x, VertexType y, EdgeType e)
{
    if (x < 0 || y < 0 || x >= MAX_VERTEX_NUM || y >= MAX_VERTEX_NUM)
    {
        return false;
    }
    if (g.vertex[x] == 0 || g.vertex[y] == 0)
    {
        return false;
    }
    g.edge[x][y] = e;
    g.edge[y][x] = e;
    return true;
}

void Visit(VertexType v)
{
    cout << v << " ";
}

void RandomInitGraph(Graph &g)
{
    memset(&g, 0, sizeof(Graph));
    int temp1, temp2;
    for (size_t i = 0; i < MAX_VERTEX_NUM * 2; i++)
    {
        temp1 = rand() % MAX_VERTEX_NUM;
        InsertVertex(g, temp1);
    }
    for (size_t i = 0; i < MAX_VERTEX_NUM * 2; i++)
    {
        temp1 = rand() % MAX_VERTEX_NUM;
        temp2 = rand() % MAX_VERTEX_NUM;
        AddEdge(g, temp1, temp2);
    }
}

void DisplayGraph(Graph &g)
{
    cout << "vertex: ";
    for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
    {
        if (g.vertex[i] != 0)
        {
            cout << i << " ";
        }
    }
    cout << endl;
    cout << "\033[4m  │\033[0m";
    for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
    {
        printf("\033[4m%2d \033[0m", i);
    }
    cout << endl;
    for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
    {
        printf("%-2d│", i);
        for (VertexType j = 0; j < MAX_VERTEX_NUM; j++)
        {
            if (g.edge[i][j] != 0)
            {
                printf("%2d ", g.edge[i][j]);
            }
            else
            {
                printf(" - ");
            }
        }
        cout << endl;
    }
}

void BFS(Graph &g, VertexType v, bool visited[])
{
    Visit(v);
    visited[v] = true;
    queue<VertexType> q;
    q.push(v);
    while (!q.empty())
    {
        v = q.front();
        q.pop();
        for (VertexType w = FirstNeighbor(g, v); w >= 0; w = NextNeighbor(g, v, w))
        {
            if (!visited[w])
            {
                Visit(w);
                visited[w] = true;
                q.push(w);
            }
        }
    }
}

void BFSTraverse(Graph &g)
{
    bool visited[MAX_VERTEX_NUM];
    memset(visited, 0, sizeof(bool) * MAX_VERTEX_NUM);
    for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
    {
        if (!visited[i] && g.vertex[i] != 0)
        {
            BFS(g, i, visited);
            cout << endl;
        }
    }
}

void DFS(Graph &g, VertexType v, bool visited[])
{
    Visit(v);
    visited[v] = true;
    for (VertexType i = FirstNeighbor(g, v); i >= 0; i = NextNeighbor(g, v, i))
    {
        if (!visited[i])
        {
            DFS(g, i, visited);
        }
    }
}

void DFSTraverse(Graph &g)
{
    bool visited[MAX_VERTEX_NUM];
    memset(visited, 0, sizeof(bool) * MAX_VERTEX_NUM);
    for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
    {
        if (!visited[i] && g.vertex[i] != 0)
        {
            DFS(g, i, visited);
            cout << endl;
        }
    }
}

void RandomSetWeight(Graph &g)
{
    for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
    {
        for (VertexType j = 0; j < MAX_VERTEX_NUM; j++)
        {
            if (g.edge[i][j] > 0)
            {
                g.edge[i][j] = rand() % (MAX_VERTEX_NUM - 1) + 1;
                g.edge[j][i] = g.edge[i][j];
            }
        }
    }
}

//最小生成树算法普里姆
void Prim(Graph &g, Graph &t)
{
    memset(&t, 0, sizeof(Graph));
    //寻找第一个图节点作为起始节点
    VertexType v;
    for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
    {
        if (g.vertex[i] != 0)
        {
            v = i;
            break;
        }
    }
    InsertVertex(t, v);
    EdgeType minDist = EDGE_TYPE_MAX; //给个最大值
    VertexType nextVertex1;
    VertexType nextVertex2;
    while (t.vexNum != g.vexNum)
    {
        minDist = EDGE_TYPE_MAX;
        //找到t中已有节点的最小的边，且该节点不属于t
        for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
        {
            if (t.vertex[i] != 0)
            {
                //遍历节点，找g中该节点的各个边，找出最短边
                for (VertexType j = FirstNeighbor(g, i); j >= 0; j = NextNeighbor(g, i, j))
                {
                    if (t.vertex[j] == 0 && g.edge[i][j] < minDist)
                    {
                        minDist = g.edge[i][j];
                        nextVertex1 = i;
                        nextVertex2 = j;
                    }
                }
            }
        }
        InsertVertex(t, nextVertex2);
        AddEdge(t, nextVertex1, nextVertex2);
        SetEdgeValue(t, nextVertex1, nextVertex2, minDist);
    }
}

VertexType UFSFindRoot(VertexType ufs[], VertexType x)
{
    while (ufs[x] >= 0)
    {
        x = ufs[x];
    }
    return x;
}

//最小生成树算法克鲁斯卡尔
void Kruskal(Graph &g, Graph &t)
{
    memset(&t, 0, sizeof(Graph));
    VertexType ufs[MAX_VERTEX_NUM];
    //复制节点//顺便初始化一下并查集
    for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
    {
        ufs[i] = -1;
        if (g.vertex[i] != 0)
        {
            InsertVertex(t, i);
        }
    }
    EdgeType minDist = EDGE_TYPE_MAX;
    VertexType v1, v2;
    while (1)
    {
        minDist = EDGE_TYPE_MAX;
        //取出权值最小的边
        for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
        {
            if (g.vertex[i] != 0)
            {
                //遍历该顶点的所有边，找到不构成回路且权值最小的边
                for (EdgeType w = FirstNeighbor(g, i); w >= 0; w = NextNeighbor(g, i, w))
                {
                    if (GetEdgeValue(g, i, w) < minDist && (UFSFindRoot(ufs, i) != UFSFindRoot(ufs, w)))
                    {
                        minDist = GetEdgeValue(g, i, w);
                        v1 = i;
                        v2 = w;
                    }
                }
            }
        }
        if (minDist == EDGE_TYPE_MAX)
        {
            break;
        }
        //查询完所有边后，开始加入边
        AddEdge(t, v1, v2);
        SetEdgeValue(t, v1, v2, minDist);
        //处理并查集
        ufs[UFSFindRoot(ufs, v2)] = UFSFindRoot(ufs, v1);
    }
}

int main(int argc, char const *argv[])
{
    Graph g;
    RandomInitGraph(g);
    RandomSetWeight(g);
    cout << "Graph g" << endl;
    DisplayGraph(g);
    cout << "BFSTraverse" << endl;
    BFSTraverse(g);
    cout << "DFSTraverse" << endl;
    DFSTraverse(g);
    Graph t;
    cout << "Prim" << endl;
    Prim(g, t);
    DisplayGraph(t);
    Graph k;
    cout << "Kruskal" << endl;
    Kruskal(g, k);
    DisplayGraph(k);
    return 0;
}
