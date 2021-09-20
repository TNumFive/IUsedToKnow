#include <iostream>
#include <string>

using namespace std;

//基于从0开始索引的数组
void getNext(string t, size_t next[])
{
    next[0] = -1;
    //i的初始值是数组的第一个序号，j的初始值是数组的第一个格子的数值
    size_t i = 0, j = -1;
    //实际上需要计算的个数是长度减一，最后一个并不需要
    while (i < t.length() - 1)
    {
        if (j == -1 || t.at(i) == t.at(j))
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
}

void getNextval(string t, size_t nextval[])
{
    nextval[0] = -1;
    size_t i = 0, j = -1;
    while (i < t.length() - 1)
    {
        if (j == -1 || t.at(i) == t.at(j))
        {
            i++;
            j++;
            if (t.at(i) != t.at(j))
            {
                nextval[i] = j;
            }
            else
            {
                nextval[i] = nextval[j];
            }
        }
        else
        {
            j = nextval[j];
        }
    }
}

size_t IndexKMP(string s, string t, size_t next[])
{
    size_t i = 0, j = 0;
    while (i < s.length() && j < t.length())
    {
        if (j == -1 || s.at(i) == t.at(j))
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if (j >= t.length())
    {
        return i - t.length();
    }
    else
    {
        return -1;
    }
}

int main(int argc, char const *argv[])
{
    string m = "aabaabaabaac";
    string p = "aabaac";
    size_t next[p.length()];
    cout << m << endl;
    cout << p << endl;
    cout << "next数组" << endl;
    getNext(p, next);
    for (size_t i = 0; i < p.length(); i++)
    {
        //为了避免使用-1导致的位数无法对齐，这里整体+1方便观察
        cout << (int64_t)next[i] + 1;
    }
    cout << endl;
    cout << "nextval数组" << endl;
    getNextval(p, next);
    for (size_t i = 0; i < p.length(); i++)
    {
        //为了避免使用-1导致的位数无法对齐，这里整体+1方便观察
        cout << (int64_t)next[i] + 1;
    }
    cout << endl;
    cout << "index by KMP:" << (int64_t)IndexKMP(m, p, next) << endl;
    cout << "index by find():" << m.find(p) << endl;
    return 0;
}