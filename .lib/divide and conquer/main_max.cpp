#include <iostream>

using namespace std;

#define ARR_SIZE 1000
#define RATIO 10
#define MIN_INT -0x7FFFFFFF

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

struct Divider {
    int arr[ARR_SIZE];
    int preSum[ARR_SIZE / RATIO];
    Divider() {
        for (int i = 0; i < ARR_SIZE; i++) {
            arr[i] = 0;
        }
        for (int i = 0; i < ARR_SIZE / RATIO; i++) {
            preSum[i] = 0;
        }
    }
    void set(int index, int newValue) {
        preSum[index / RATIO] = MIN_INT;
        arr[index] = newValue;
        int i = index / RATIO;
        for (int k = 0; k < RATIO; ++k, ++i)
            preSum[index / RATIO] = max(arr[index], preSum[index / RATIO]);
    }
    void update(int index, int change) {
        arr[index] += change;
        preSum[index / RATIO] = max(arr[index], preSum[index / RATIO]);
    }
    int getMax(int start, int ends) {
        int Max = MIN_INT;
        for (int i = start; i <= ends; i++) {
            if ((i % RATIO == 0) && ((i + RATIO - 1) <= ends)) {
                Max = max(preSum[i / RATIO], Max);
                i += RATIO - 1;
            } else
                Max = max(arr[i], Max);
        }
        return Max;
    }
} dv;

int main() {
    int sum = 0;
    Divider dv;

    for (int i = 0; i < 100; i++) {
        dv.update(i, rand() % 50);
        if (i <= 89 && i >= 5)
            sum = max(dv.arr[i], sum);
    }

    cout << dv.getMax(5, 89) << endl;

    cout << sum;
    return 0;
}