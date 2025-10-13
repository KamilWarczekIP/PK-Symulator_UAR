#include <iostream>
#include <chrono>
#include "ARX.h"


int main()
{
    ARX arx({0.4, 0.7, 0.44, 0.6}, { -0.6, -3.0, 2.1, 6.7}, 1);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for(int i = 0; i < 10000; i++)
        arx.tick(1.0);


    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
}
