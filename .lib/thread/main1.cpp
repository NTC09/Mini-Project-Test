#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

void thread1() {
    cout << "Thread1 running" << endl;
}

mutex m;

int main() {
    thread runner1(thread1);
    if (runner1.joinable()) {
        runner1.join();
    }

    runner1.detach();
    return 0;
}