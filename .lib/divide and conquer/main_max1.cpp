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
    if (diff < 0 && segment[i / rate] == arr[i]) {
        int i0 = i - (i % rate);
        arr[i] += diff;
        segment[i / rate] += diff;
        for (int j = i0; j < i0 + rate; ++j)
            segment[j / rate] = max(arr[j], segment[j / rate]);
    } else {
        arr[i] += diff;
        segment[i / rate] = max(arr[i], segment[i / rate]);
    }
}

void update(int i1, int i2, int diff) {
    int i0 = i1 - (i1 % rate);
    for (; i1 <= i2;) {
        if (i1 % rate == 0 && i1 + rate - 1 <= i2) {
            segment[i1 / rate] += diff;
            i1 += rate;
        } else {
            arr[i1] += diff;
            i1 += 1;
        }
    }
    segment[i0 / rate] = arr[i0];
    for (int j = i0; j < i0 + rate; ++j)
        segment[j / rate] = max(arr[j], segment[j / rate]);
    i0 = i2 - (i2 % rate);
    segment[i0 / rate] = arr[i0];
    for (int j = i0; j < i0 + rate; ++j)
        segment[j / rate] = max(arr[j], segment[j / rate]);
}

int query(int i1, int i2) {
    int res = INT_MIN;
    for (; i1 <= i2;) {
        if (i1 % rate == 0 && i1 + rate - 1 <= i2) {
            res = max(segment[i1 / rate], res);
            i1 += rate;
        } else {
            res = max(arr[i1], res);
            i1 += 1;
        }
    }
    return res;
}

int main() {
    init(16);
    for (int i = 0; i < 16; i++) {
        update(i, rand() % 50);
        cout << arr[i] << " ";
    }

    update(0, -10);
    update(2, 8, -10);
    cout << endl;
    cout << query(0, 5) << endl;

    return 0;
}