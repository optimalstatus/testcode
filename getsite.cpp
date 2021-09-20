#include <string>
#include <atomic>
#include <mutex>
#include <iostream>
#include <thread>

volatile bool CacheReady = false;
std::mutex m;

std::string SiteId;
bool switcher = false;


std::string FillAndGetCache()
{
    if (!CacheReady)
    {
        std::lock_guard<std::mutex> lock(m);
        if (!CacheReady)
        {
            if (!switcher) SiteId = "abcdefghijklmnopqrstuvwxyz1234567890123456789012345678901234567890!!";
            else SiteId = "123456789012345678901234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ--";
            switcher = !switcher;
            CacheReady = true; // cache is ready
        }

    }
    return SiteId;

}

void ReadCache()
{
    while(true)
    {
        std::string s = FillAndGetCache();
        if (s != "abcdefghijklmnopqrstuvwxyz1234567890123456789012345678901234567890!!" && s != "123456789012345678901234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ--")
        {
            std::cout << "unexpected siteid:" << s << "\n";
        }
        CacheReady = false; // make cache invalid again
    }
}

int main()
{
    std::thread t1(ReadCache);
    std::thread t2(ReadCache);
    t1.join();
    t2.join();
    return 0;
}

