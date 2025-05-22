#include <iostream>
using namespace std;

template <typename TYPE>
class SegmentTree {
    private:
    TYPE* STree;
    TYPE size;
    TYPE level;

    public:
    void init(TYPE arrSize) {
        level = 0;
        while (power(2, level) < arrSize)
            level++;
        size = 2 * power(2, level) - 1;
        STree = new TYPE[size];
    }
    TYPE power(TYPE a, TYPE n) {
        if (n == 1) return a;
        if (n == 0) return 1;
        TYPE p = power(a, n / 2);
        if (a & 0b1) return p * p * a;
        return p * p;
    }
    void updateInternal(TYPE index, TYPE left, TYPE right, TYPE i, TYPE value) {
        if (i < left || i > right) return;
        if (left == right) STree[index] = value;
        TYPE mid = (left + right) / 2;
        updateInternal(index * 2 + 1, left, mid, i, value);
        updateInternal(index * 2 + 2, left, mid, i, value);
        STree[index] = STree[index * 2 + 1] + STree[index * 2 + 2];
    }
    void update(TYPE i, TYPE value) { updateInternal(0, 0, size, i, value); }
    TYPE getSumOfSectionInternal(TYPE index,
                                 TYPE start,
                                 TYPE end,
                                 TYPE left,
                                 TYPE right) {
        if (start < left || end > right) return 0;
        TYPE sum = 0;
        if (start <= left && end >= right) {
            return STree[index];
        }
        TYPE mid = (left + right) / 2;
        return sum +
               getSumOfSectionInternal(index * 2 + 1, left, mid, start, end) +
               getSumOfSectionInternal(index * 2 + 2, mid + 1, right, start,
                                       end);
    }
    TYPE getSumOfSection(TYPE start, TYPE end) {
        return getSumOfSectionInternal(0, 0, size, start, end);
    }
};

int main() {
    SegmentTree<int> stree;
    stree.init(16);
    for (int i = 0; i < 16; i++) {
        stree.update(i, i);
    }
    cout << stree.getSumOfSection(0, 16);
    return 0;
}