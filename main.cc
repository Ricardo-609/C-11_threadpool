#include "ThreadPool.h"
#include <cmath>

int sum1(int a, int b)
{
    this_thread::sleep_for(chrono::seconds(2));
    // 比较耗时
    return a + b;
}
int sum2(int a, int b, int c)
{
    this_thread::sleep_for(chrono::seconds(2));
    return a + b + c;
}

int main()
{
    ThreadPool pool;
    // pool.setMode(PoolMode::MODE_CACHED);
    pool.start();

    std::future<int> r1 = pool.submitTask(sum1, 1, 2);
    std::future<int> r2 = pool.submitTask(sum2, 1, 2, 3);
    std::future<int> r3 = pool.submitTask([](int start, int end) -> int
                                          {
        int sum = 0;
        for (int i = start; i <= end; i++)
            sum += i;
        return sum; },
                                          1, 100);
    std::future<int> r4 = pool.submitTask([](int start, int end) -> int
                                          {
        int sum = 0;
        for (int i = start; i <= end; i++)
            sum += i;
        return sum; },
                                          1, 100);
    // std::future<int> r5 = pool.submitTask([](int b, int e)->int {
    //     int sum = 0;
    //     for (int i = start; i <= end; i++)
    //         sum += i;
    //     return sum;
    //     }, 1, 100);
    // std::future<int> r4 = pool.submitTask(sum1, 1, 2);

    std::cout << r1.get() << std::endl;
    std::cout << r2.get() << std::endl;
    std::cout << r3.get() << std::endl;
    std::cout << r4.get() << std::endl;
    // std::cout << r5.get() << std::endl;
}