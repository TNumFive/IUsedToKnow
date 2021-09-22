#include <iostream>
using namespace std;

#define SIZE 100
int UFSets[SIZE];

void Initial(int s[])
{
    for (size_t i = 0; i < SIZE; i++)
    {
        s[i] = -1;
    }
}

int Find(int s[], int x)
{
    while (s[x] > 0)
    {
        x = s[x];
    }
    return x;
}

//root1与root2需不同，且各自表示集合的名字
void Union(int s[], int root1, int root2)
{
    s[root2] = root1;
}