#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <string>
using namespace std;

#define TEST(name, func, vec, copy)                                                \
    {                                                                              \
        copy = vec;                                                                \
        ssize_t timer = TimeConsumed(func, copy);                                  \
        bool isCorrect = IsNonDecreasing(copy);                                    \
        printf("%s:%10ldus %s\n", name, timer, (isCorrect ? "correct" : "wrong")); \
    }

typedef int ElemType;

void InitVector(vector<ElemType> &vec, size_t size)
{
    vec.clear();
    srand(0);
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
    ssize_t low, high, mid, j;
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

//希尔排序
void ShellSort(vector<ElemType> &vec)
{
    ElemType temp;
    ssize_t j;
    for (ssize_t d = vec.size() / 2; d >= 1; d = d / 2)
    {
        for (ssize_t i = d; i < vec.size(); i++)
        {
            if (vec[i] < vec[i - d])
            {
                temp = vec[i];
                for (j = i - d; j >= 0 && vec[j] > temp; j -= d)
                {
                    vec[j + d] = vec[j];
                }
                vec[j + d] = temp;
            }
        }
    }
}

//冒泡排序
void BubbleSort(vector<ElemType> &vec)
{
    bool flag = true;
    ElemType temp;
    for (size_t i = 0; i < vec.size() - 1; i++)
    {
        flag = false;
        for (size_t j = vec.size() - 1; j > i; j--)
        {
            if (vec[j - 1] > vec[j])
            {
                flag = true;
                temp = vec[j];
                vec[j] = vec[j - 1];
                vec[j - 1] = temp;
            }
        }
        if (flag = false)
        {
            return;
        }
    }
}

//快速排序
ssize_t Partition(vector<ElemType> &vec, ssize_t low, ssize_t high)
{
    ElemType pivot = vec[low];
    while (low < high)
    {
        while (low < high && vec[high] >= pivot)
        {
            high--;
        }
        vec[low] = vec[high];
        while (low < high && vec[low] <= pivot)
        {
            low++;
        }
        vec[high] = vec[low];
    }
    vec[low] = pivot;
    return low;
}
void QuickSortRecursion(vector<ElemType> &vec, ssize_t low, ssize_t high)
{
    if (low < high)
    {
        ssize_t pivotpos = Partition(vec, low, high);
        QuickSortRecursion(vec, low, pivotpos - 1);
        QuickSortRecursion(vec, pivotpos + 1, high);
    }
}
void QuickSortRecursion(vector<ElemType> &vec)
{
    QuickSortRecursion(vec, 0, vec.size());
}
void QuickSortStack(vector<ElemType> &vec)
{
    queue<ssize_t> range;
    ssize_t low, high;
    range.push(0);
    range.push(vec.size());
    while (!range.empty())
    {
        low = range.front();
        range.pop();
        high = range.front();
        range.pop();
        ssize_t pivotPos = Partition(vec, low, high);
        if (low < pivotPos - 1)
        {
            range.push(low);
            range.push(pivotPos - 1);
        }
        if (pivotPos + 1 < high)
        {
            range.push(pivotPos + 1);
            range.push(high);
        }
    }
}

//选择排序
void SelectSort(vector<ElemType> &vec)
{
    size_t min;
    ElemType temp;
    for (size_t i = 0; i < vec.size() - 1; i++)
    {
        min = i;
        for (size_t j = i + 1; j < vec.size(); j++)
        {
            if (vec[j] < vec[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            temp = vec[i];
            vec[i] = vec[min];
            vec[min] = temp;
        }
    }
}

//堆排序
void HeapAjust(vector<ElemType> &vec, size_t root, size_t size)
{
    ElemType temp = vec[root];
    //i = root * 2 + 1 => lchild
    for (size_t i = root * 2 + 1; i < size; i = i * 2 + 1)
    {
        if (i + 1 < size && vec[i] < vec[i + 1])
        {
            i++;
        }
        if (temp >= vec[i])
        {
            break;
        }
        else
        {
            vec[root] = vec[i];
            root = i;
        }
    }
    vec[root] = temp;
}
void BuildMaxHeap(vector<ElemType> &vec, size_t size)
{
    for (ssize_t i = size / 2 - 1; i >= 0; i--)
    {
        HeapAjust(vec, i, size);
    }
}
void HeapSort(vector<ElemType> &vec)
{
    ElemType temp;
    BuildMaxHeap(vec, vec.size());
    for (size_t i = vec.size() - 1; i > 0; i--)
    {
        temp = vec[i];
        vec[i] = vec[0];
        vec[0] = temp;
        HeapAjust(vec, 0, i);
    }
}

//归并排序 [low,mid) [mid,high)
void Merge(vector<ElemType> &vec, size_t low, size_t mid, size_t high)
{
    vector<ElemType> temp;
    temp.reserve(high - low + 1);
    size_t i = low, j = mid + 1;
    while (i <= mid && j <= high)
    {
        if (vec[i] <= vec[j])
        {
            temp.push_back(vec[i]);
            i++;
        }
        else
        {
            temp.push_back(vec[j]);
            j++;
        }
    }
    while (i <= mid)
    {
        temp.push_back(vec[i]);
        i++;
    }
    while (j <= high)
    {
        temp.push_back(vec[j]);
        j++;
    }
    for (size_t i = low; i <= high; i++)
    {
        vec[i] = temp[i - low];
    }
}
void MergeSortRecursion(vector<ElemType> &vec, size_t low, size_t high)
{
    if (low < high)
    {
        size_t mid = (low + high) / 2;
        MergeSortRecursion(vec, low, mid);
        MergeSortRecursion(vec, mid + 1, high);
        Merge(vec, low, mid, high);
    }
}
void MergeSort(vector<ElemType> &vec)
{
    MergeSortRecursion(vec, 0, vec.size() - 1);
}

int main(int argc, char const *argv[])
{
    vector<ElemType> vec;
    vector<ElemType> copy;
    InitVector(vec, 11111);
    // cout << "DisplayVector" << endl;
    // DisplayVector(vec, 20);
    TEST("InsertionSort      \t", InsertionSort, vec, copy);
    TEST("BinaryInsertionSort\t", BinaryInsertionSort, vec, copy);
    TEST("ShellSort          \t", ShellSort, vec, copy);
    TEST("BubbleSort         \t", BubbleSort, vec, copy);
    TEST("QuickSortRecursion \t", QuickSortRecursion, vec, copy);
    TEST("QuickSortStack     \t", QuickSortStack, vec, copy);
    TEST("SelectSort         \t", SelectSort, vec, copy);
    TEST("HeapSort           \t", HeapSort, vec, copy);
    TEST("MergeSort          \t", MergeSort, vec, copy);
    return 0;
}
