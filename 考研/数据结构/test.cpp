#include <iostream>
#include <chrono>

using namespace std;

#define TEST_NUM 1000000

int64_t TimeConsumed(void (*func)())
{
    auto start = chrono::high_resolution_clock::now();
    func();
    auto end = chrono::high_resolution_clock::now();
    auto consumed = std::chrono::duration_cast<chrono::microseconds>(end - start);
    return consumed.count();
}

void Add()
{
    int64_t temp = 0;
    for (size_t i = 0; i < TEST_NUM; i++)
    {
        temp++;
    }
}

void Minus()
{
    int64_t temp = INT64_MAX;
    for (size_t i = 0; i < TEST_NUM; i++)
    {
        temp--;
    }
}

void Multiply()
{
    int64_t temp = 1;
    for (size_t i = 0; i < TEST_NUM; i++)
    {
        temp *= 1;
    }
}

void Divide()
{
    int64_t temp = 1;
    for (size_t i = 0; i < TEST_NUM; i++)
    {
        temp /= 1;
    }
}

void Assign()
{
    int64_t temp1 = 0, temp2 = 0;
    for (size_t i = 0; i < TEST_NUM; i++)
    {
        temp1+=rand()%10-5;
        temp2 = temp1;
    }
}

void Compare()
{
    int64_t temp1 = 0, temp2 = 0, temp3 = 0;
    for (size_t i = 0; i < TEST_NUM; i++)
    {
        if (temp1 > temp2)
        {
            temp2+=rand()%10-5;
            temp3 = temp2;
        }
        else
        {
            temp1+=rand()%10-5;
            temp3 = temp1;
        }
    }
}

int main(int argc, char const *argv[])
{
    printf("%s:%10ldus\n", "Add", TimeConsumed(Add));
    printf("%s:%10ldus\n", "Minus", TimeConsumed(Minus));
    printf("%s:%10ldus\n", "Multiply", TimeConsumed(Multiply));
    printf("%s:%10ldus\n", "Divide", TimeConsumed(Divide));
    printf("%s:%10ldus\n", "Assign", TimeConsumed(Assign));
    printf("%s:%10ldus\n", "Compare", TimeConsumed(Compare));
    return 0;
}
