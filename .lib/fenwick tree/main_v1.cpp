#include <iostream>

using namespace std;

#define TREE_SIZE 1000

struct FenwickTree {
    int bit[TREE_SIZE + 1];
    void init(int n) {
        for (int i = 0; i < n + 1; i++)
            bit[i] = 0;
    }
    int getSum(int index) {
        int sum = 0;
        ++index;
        while (index > 0) {
            sum += bit[index];
            index -= index & (-index);
        }
        return sum;
    }
    void update(int index, int val) {
        ++index;
        while (index <= TREE_SIZE) {
            bit[index] += val;
            index += index & (-index);
        }
    }
};

int main() {
    return 0;
}