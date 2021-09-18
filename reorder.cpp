#include <string>
#include <atomic>
#include <mutex>
#include <iostream>
#include <thread>
#include <cassert>
#include <unistd.h>

volatile bool CacheReady = false;
std::string SiteId;
std::mutex m;

void FillCache(int i)
{
    if (!CacheReady)
    {
        std::lock_guard<std::mutex> lock(m);
        if (!CacheReady)
        {
            SiteId[i] = 'X';
            CacheReady = true;
        }

    }
}

void TestCache()
{
    while(!CacheReady) ;
    assert(SiteId[9] == 'X');
    std::cout << "test done\n";
}

int main()
{
    std::thread t2(TestCache);
    usleep(120);
    std::thread t1(FillCache, 9);
    t1.join();
    t2.join();
    return 0;
}

