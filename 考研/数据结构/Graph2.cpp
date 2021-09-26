/**
 * Graph针对的是无向图的一些算法，使用0作为无穷标识符，在有向图比较中比较不和
 * 此文件定义了最大可表示值来代表无穷
 */
#include <iostream>
#include <cstring>
#include <queue>
#include <list>
using namespace std;

#define MAX_VERTEX_NUM 10
#define EDGE_TYPE_MAX INT32_MAX
typedef int VertexType;
typedef int EdgeType;
typedef struct
{
    //简单使用对应需要里的节点值不为0代表该节点存在，简化判断
    VertexType vertex[MAX_VERTEX_NUM];
    //使用EDGE_TYPE_MAX代表无穷=》后续可考虑浮点数，天然自带无穷；
    EdgeType edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    size_t vexNum, arcNum;
} Graph;

bool Adjacent(Graph &g, VertexType x, VertexType y)
{
    if (x < 0 || y < 0 || x >= MAX_VERTEX_NUM || y >= MAX_VERTEX_NUM)
    {
        return false;
    }
    if (g.edge[x][y] != EDGE_TYPE_MAX)
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
    if (g.vertex[x] != 0)
    {
        g.vexNum--;
        g.vertex[x] = 0;
    }
    //去边
    for (size_t i = 0; i < MAX_VERTEX_NUM; i++)
    {
        if (g.edge[i][x] != EDGE_TYPE_MAX)
        {
            g.edge[i][x] = EDGE_TYPE_MAX;
            g.arcNum--;
        }
        if (g.edge[x][i] != EDGE_TYPE_MAX)
        {
            g.edge[x][i] = EDGE_TYPE_MAX;
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
    if (g.edge[x][y] == EDGE_TYPE_MAX)
    {
        g.edge[x][y] = 0;
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
    if (g.edge[x][y] != EDGE_TYPE_MAX)
    {
        g.edge[x][y] = EDGE_TYPE_MAX;
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
        if (g.edge[x][i] != EDGE_TYPE_MAX)
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
        if (g.edge[x][i] != EDGE_TYPE_MAX)
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
    return true;
}

void RandomInitGraph(Graph &g)
{
    memset(&g, 0, sizeof(Graph));
    for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
    {
        for (VertexType j = 0; j < MAX_VERTEX_NUM; j++)
        {
            g.edge[i][j] = EDGE_TYPE_MAX;
        }
    }
    int temp1, temp2, temp3;
    for (size_t i = 0; i < MAX_VERTEX_NUM * 2; i++)
    {
        temp1 = rand() % MAX_VERTEX_NUM;
        InsertVertex(g, temp1);
    }
    for (size_t i = 0; i < MAX_VERTEX_NUM * 2; i++)
    {
        temp1 = rand() % MAX_VERTEX_NUM;
        temp2 = rand() % MAX_VERTEX_NUM;
        temp3 = rand() % (MAX_VERTEX_NUM - 1) + 1;
        AddEdge(g, temp1, temp2);
        SetEdgeValue(g, temp1, temp2, temp3);
    }
}

void InitDAG(Graph &g)
{
    memset(&g, 0, sizeof(Graph));
    for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
    {
        for (VertexType j = 0; j < MAX_VERTEX_NUM; j++)
        {
            g.edge[i][j] = EDGE_TYPE_MAX;
        }
    }
    for (VertexType i = 1; i <= 5; i++)
    {
        InsertVertex(g, i);
    }
    VertexType tail[] = {1, 1, 2, 2, 3, 4, 4};
    VertexType head[] = {2, 4, 3, 4, 5, 3, 5};
    for (VertexType i = 0; i < 7; i++)
    {
        AddEdge(g, tail[i], head[i]);
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
    cout << "\033[4m   \033[0m";
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
            if (g.edge[i][j] != EDGE_TYPE_MAX)
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

void Dijkstra(Graph &g, EdgeType dist[], VertexType path[], VertexType first = -1)
{
    //初始化距离数组，路径数组
    for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
    {
        dist[i] = EDGE_TYPE_MAX;
        path[i] = -1;
    }
    VertexType v, next;
    if (first == -1)
    {
        //选取第一个顶点
        for (v = 0; v < MAX_VERTEX_NUM; v++)
        {
            if (g.vertex[v] != 0)
            {
                break;
            }
        }
        first = v;
    }
    else
    {
        if (g.vertex[first] == 0)
        {
            return;
        }
        v = first;
    }
    //用于记录顶点和边的集合
    Graph d;
    memset(&d, 0, sizeof(d));
    for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
    {
        for (VertexType j = 0; j < MAX_VERTEX_NUM; j++)
        {
            d.edge[i][j] = EDGE_TYPE_MAX;
        }
    }
    //加入第一个顶点
    InsertVertex(d, v);
    //初始化数值
    for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
    {
        //不更新自己，不更新距离为无穷的
        if (i != v && GetEdgeValue(g, v, i) != EDGE_TYPE_MAX)
        {
            dist[i] = GetEdgeValue(g, v, i);
            path[i] = i;
        }
    }
    EdgeType minDist;
    //所有节点完成则退出
    while (d.vexNum < g.vexNum)
    {
        minDist = EDGE_TYPE_MAX;
        for (v = 0; v < MAX_VERTEX_NUM; v++)
        {
            //距离最短，且未被加入
            if (minDist > dist[v] && d.vertex[v] == 0)
            {
                minDist = dist[v];
                next = v;
            }
        }
        //找不到下一条边了
        if (minDist == EDGE_TYPE_MAX)
        {
            break;
        }
        //找到下一个节点
        InsertVertex(d, next);
        //更新到各点的距离
        for (EdgeType j = FirstNeighbor(g, next); j >= 0; j = NextNeighbor(g, next, j))
        {
            if (dist[j] - dist[next] > +GetEdgeValue(g, next, j) && j != first)
            {
                dist[j] = dist[next] + GetEdgeValue(g, next, j);
                path[j] = next;
            }
        }
    }
}

void Floyd(Graph &g)
{
    //初始化数组
    EdgeType a[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
    {
        for (VertexType j = 0; j < MAX_VERTEX_NUM; j++)
        {
            a[i][j] = GetEdgeValue(g, i, j);
        }
    }
    //循环查找
    for (VertexType k = 0; k < MAX_VERTEX_NUM; k++)
    {
        if (g.vertex[k] == 0)
        {
            continue;
        }
        for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
        {
            if (g.vertex[i] == 0)
            {
                continue;
            }
            for (VertexType j = 0; j < MAX_VERTEX_NUM; j++)
            {
                if (g.vertex[j] == 0 || i == j)
                {
                    continue;
                }
                //注意溢出问题，在a、b、c均为正数时 "a>b+c => a-b>c"
                if (a[i][j] - a[i][k] > a[k][j])
                {
                    a[i][j] = a[i][k] + a[k][j];
                }
            }
        }
    }
    cout << "\033[4m   \033[0m";
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
            if (a[i][j] != EDGE_TYPE_MAX)
            {
                printf("%2d ", a[i][j]);
            }
            else
            {
                cout << " - ";
            }
        }
        cout << endl;
    }
}

bool TopologicalSort(Graph &g)
{
    Graph t;
    memcpy(&t, &g, sizeof(Graph));
    bool flag = true;
    while (flag)
    {
        flag = false;
        for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
        {
            //顶点存在
            if (t.vertex[i] != 0)
            {
                VertexType j;
                for (j = 0; j < MAX_VERTEX_NUM; j++)
                {
                    if (GetEdgeValue(t, j, i) != EDGE_TYPE_MAX)
                    {
                        break;
                    }
                }
                if (j == MAX_VERTEX_NUM)
                {
                    cout << i << " ";
                    DeleteVertex(t, i);
                    flag = true;
                }
            }
        }
    }
    cout << endl;
    if (t.vexNum == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char const *argv[])
{
    Graph g;
    cout << "Random init directed graph" << endl;
    RandomInitGraph(g);
    DisplayGraph(g);
    {
        cout << "Dijstra - min distance - path matrix" << endl;
        EdgeType dist[MAX_VERTEX_NUM];
        VertexType path[MAX_VERTEX_NUM];
        cout << "\033[4m   \033[0m";
        for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
        {
            printf("\033[4m%2d \033[0m", i);
        }
        cout << "\t\033[4m   \033[0m";
        for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
        {
            printf("\033[4m%2d \033[0m", i);
        }
        cout << endl;
        for (VertexType i = 0; i < MAX_VERTEX_NUM; i++)
        {
            Dijkstra(g, dist, path, i);
            printf("%-2d│", i);
            for (VertexType j = 0; j < MAX_VERTEX_NUM; j++)
            {
                if (dist[j] != EDGE_TYPE_MAX)
                {
                    printf("%2d ", dist[j]);
                }
                else
                {
                    printf(" - ");
                }
            }
            printf("\t%-2d│", i);
            for (VertexType j = 0; j < MAX_VERTEX_NUM; j++)
            {
                if (path[j] != -1)
                {
                    printf("%2d ", path[j]);
                }
                else
                {
                    printf(" - ");
                }
            }
            cout << endl;
        }
    }
    cout << "Floyd - min distance" << endl;
    Floyd(g);
    {
        Graph t;
        InitDAG(t);
        cout << "Graph t" << endl;
        DisplayGraph(t);
        cout << "TopologicalSort" << endl;
        bool isTopological = TopologicalSort(t);
        if (isTopological)
        {
            cout << "graph t is topological" << endl;
        }
        else
        {
            cout << "graph t isn't topological" << endl;
        }
    }
    return 0;
}
