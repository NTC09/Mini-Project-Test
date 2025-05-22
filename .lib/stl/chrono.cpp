#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
using namespace std::chrono;

int __init = []() -> int {
    int s = 1;
    return s * 1234;
}();

void (*functions[2])() = {
    []() {},
    []() {},
};

void * (*(*fp1)(int))[10];

int main() {
    auto st = high_resolution_clock::now();

    double time;
    while (true) {
        auto en = high_resolution_clock::now();
        time = duration_cast<nanoseconds>(en - st).count();
        if (time > 1e9) break;
    }
    cout << fixed << time / 1e9;
    cout << endl << __init;
    return 0;
}