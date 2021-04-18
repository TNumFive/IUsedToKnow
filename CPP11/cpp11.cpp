#include <iostream>
#include <chrono>
#include <functional>

long fibonacci(unsigned n)
{
    if (n < 2) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main()
{
    std::function<long(unsigned)> f_fibonacci = fibonacci;
    std::function<long(unsigned)> f=std::bind(f_fibonacci,std::placeholders::_1);
    auto start = std::chrono::steady_clock::now();
    std::cout << "f(42) = " << f(42) << '\n';
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}