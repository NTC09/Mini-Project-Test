#include <cmath>
#include <iostream>

using namespace std;

int arr[10000];
int segment[100];
int rate;
int sector;
int n;

void init(int size) {
    n = size;
    rate = sqrt(size);
    sector = n / rate;

    for (int i = 0; i < n; ++i)
        arr[i] = 0;
    for (int i = 0; i < sector; ++i)
        segment[i] = 0;
}

void update(int i, int diff) {
    arr[i] += diff;
    segment[i / rate] += diff;
}

void update(int i1, int i2, int diff) {
    for (; i1 <= i2;) {
        if (i1 % rate == 0 && i1 + rate - 1 <= i2) {
            segment[i1 / rate] += diff * rate;
            i1 += rate;
        } else {
            arr[i1] += diff;
            segment[i1 / rate] += diff;
            i1 += 1;
        }
    }
}

int query(int i1, int i2) {
    int sum = 0;
    for (; i1 <= i2;) {
        if (i1 % rate == 0 && i1 + rate - 1 <= i2) {
            sum += segment[i1 / rate];
            i1 += rate;
        } else {
            sum +=  arr[i1];
            i1 += 1;
        }
    }
    return sum;
}

int main() {
    init(100);
    for (int i = 0; i < 100; i++) {
        update(i, rand() % 50);
    }

    cout << query(0, 5) << endl;

    return 0;
}