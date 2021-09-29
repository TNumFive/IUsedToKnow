#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

#define TEST(name, func, vec, copy)                                                \
    {                                                                              \
        copy = vec;                                                                \
        int64_t timer = TimeConsumed(func, copy);                                  \
        bool isCorrect = IsNonDecreasing(copy);                                    \
        printf("%s:%10ldus %s\n", name, timer, (isCorrect ? "correct" : "wrong")); \
    }

typedef int ElemType;

void InitVector(vector<ElemType> &vec, size_t size)
{
    vec.clear();
    for (size_t i = 0; i < size; i++)
    {
        vec.push_back(rand() % size);
    }
}

bool IsNonDecreasing(vector<ElemType> &vec)
{
    for (size_t i = 0; i < vec.size() - 1; i++)
    {
        if (vec[i] > vec[i + 1])
        {
            return false;
        }
    }
    return true;
}

void DisplayVector(vector<ElemType> &vec, size_t rowLength)
{
    cout << "DisplayVector" << endl;
    for (size_t i = 0; i < vec.size(); i++)
    {
        printf("%-4d", vec[i]);
        if ((i + 1) % rowLength == 0)
        {
            cout << endl;
        }
        else
        {
            cout << " ";
        }
    }
    if ((vec.size() + 1) % rowLength != 0)
    {
        cout << endl;
    }
}

int64_t TimeConsumed(void (*func)(vector<ElemType> &), vector<ElemType> &vec)
{
    auto start = chrono::high_resolution_clock::now();
    func(vec);
    auto end = chrono::high_resolution_clock::now();
    auto consumed = std::chrono::duration_cast<chrono::microseconds>(end - start);
    return consumed.count();
}

//插入排序
void InsertionSort(vector<ElemType> &vec)
{
    ElemType temp;
    size_t j;
    for (size_t i = 1; i < vec.size(); i++)
    {
        if (vec[i - 1] > vec[i])
        {
            temp = vec[i];
            //有序序列反向查找
            for (j = i - 1; vec[j] > temp && j >= 0; j--)
            {
                vec[j + 1] = vec[j];
            }
            vec[j + 1] = temp;
        }
    }
}

//折半插入排序
void BinaryInsertionSort(vector<ElemType> &vec)
{
    ElemType temp;
    int64_t low, high, mid, j;
    for (size_t i = 1; i < vec.size(); i++)
    {
        temp = vec[i];
        low = 0;
        high = i - 1;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (vec[mid] > temp)
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        for (j = i - 1; j >= high + 1; --j)
        {
            vec[j + 1] = vec[j];
        }
        vec[high + 1] = temp;
    }
}

int main(int argc, char const *argv[])
{
    vector<ElemType> vec;
    vector<ElemType> copy;
    InitVector(vec, 10000);
    // DisplayVector(vec, 20);
    TEST("IS\t", InsertionSort, vec, copy);
    TEST("BIS\t", BinaryInsertionSort, vec, copy);
    return 0;
}
