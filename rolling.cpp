#include <cstdint>
#include <iostream>
#include <thread>

volatile uint64_t sharedValue = 0;  // initializer = one of the 2 values!

void writer() {
    for (;;) {
        sharedValue = 0;
        sharedValue = -1ULL;  // unrolling is vastly simpler than an if

    }

}

void reader() {
    for (;;) {
        uint64_t val = sharedValue;
        uint32_t low = val, high = val>>32;
        if (low != high) {
            std::cout << "Tearing! Value: " << std::hex << val << '\n';

        }

    }

}

int main()
{
    std::thread t1(writer);
    std::thread t2(reader);
    t1.join();
    t2.join();
    return 0;

}
