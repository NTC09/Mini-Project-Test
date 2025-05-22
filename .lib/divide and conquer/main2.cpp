#include <iostream>

using namespace std;

#define ARR_SIZE 1000
#define RATIO 10

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
        preSum[index / RATIO] -= arr[index];
        arr[index] = newValue;
        preSum[index / RATIO] += arr[index];
    }

    void update(int index, int change) {
        arr[index] += change;
        preSum[index / RATIO] += change;
    }
    int getSum(int start, int ends) {
        int sum = 0;
        for (int i = start; i <= ends; i++) {
            if ((i % RATIO == 0) && ((i + RATIO - 1) <= ends)) {
                sum += preSum[i / RATIO];
                i += RATIO - 1;
            } else
                sum += arr[i];
        }
        return sum;
    }
} dv;

int main() {
    int sum = 0;
    Divider dv;

    for (int i = 0; i < 100; i++) {
        dv.update(i, rand() % 50);
        if (i <= 89 && i >= 5)
            sum += dv.arr[i];
    }

    cout << dv.getSum(5, 89) << endl;

    cout << sum;
    return 0;
}