#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

#define ABS(a) ((a) < 0 ? -(a) : (a))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int main() {
    cout << (0b010100 & (-0b010100)) << endl;
    int a = 1;
    int b = 100000;
    int arr[10000];
    int diff = ABS(a - b), maxStep = 0;
    cout << a << ", " << b << " d= " << diff << endl;
    auto st = high_resolution_clock::now();
    for (int i = 0; i < 50000; i++) {
        arr[i%10000] = i;

        /*int d = 0, l = 0, r = b, step = 0;
        diff = i%50000;
        while (true) {
            step++;
            d = (l + r) / 2;
            //cout << d << endl;
            if (d == diff)
                break;
            if (d > diff) {
                r = d;
            } else {
                l = d;
            }
        }*/
        int d = 0, m = 49999, step = 0;
        diff = i % 50000;
        while (true) {
            step++;
            // cout << d << endl;
            if (m > 1)
                m /= 2;
            if (d == diff)
                break;
            if (d > diff) {
                d -= m;
            } else {
                d += m;
            }
        }
        if (step > maxStep)
            maxStep = step;
    }
    auto en = high_resolution_clock::now();
    double cTime = duration_cast<nanoseconds>(en - st).count();
    cout << maxStep << " " << cTime / 1e9;
    return 0;
}
