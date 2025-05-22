#include <iostream>
using namespace std;

class SegmentTree {  // Sum of section
    private:
    int* STree;
    int* lazy;
    int size;
    void updateInternal(int index, int left, int right, int i, int diff) {
        if (i < left || i > right) return;
        if (left == right) {  // leaf
            STree[index] += diff;
            return;
        }
        int mid = (left + right) / 2;
        updateInternal(index * 2 + 1, left, mid, i, diff);
        updateInternal(index * 2 + 2, mid + 1, right, i, diff);
        STree[index] = STree[index * 2 + 1] + STree[index * 2 + 2];
    }
    void updateSectionInternal(int index,
                               int diff,
                               int left,
                               int right,
                               int start,
                               int end) {
        lazyUpdate(index, left, right);
        if (left > right || left > end || right < start) return;
        if (start <= left && end >= right) {  // in range
            STree[index] += (right - left + 1) * diff;
            if (left != right) {
                lazy[index * 2 + 1] += diff;
                lazy[index * 2 + 2] += diff;
            }
            return;
        }
        int mid = (left + right) / 2;
        updateSectionInternal(index * 2 + 1, diff, left, mid, start, end);
        updateSectionInternal(index * 2 + 2, diff, mid + 1, right, start, end);
        STree[index] = STree[index * 2 + 1] + STree[index * 2 + 2];
    }

    int getSumOfSectionInternal(int index,
                                int left,
                                int right,
                                int start,
                                int end) {
        lazyUpdate(index, left, right);
        if (start > right || end < left || left > right) return 0;
        if ((start <= left && end >= right)) {
            return STree[index];
        }
        int mid = (left + right) / 2;
        return getSumOfSectionInternal(index * 2 + 1, left, mid, start, end) +
               getSumOfSectionInternal(index * 2 + 2, mid + 1, right, start,
                                       end);
    }
    void lazyUpdate(int index, int left, int right) {
        if (lazy[index] != 0) {
            STree[index] = (right - left + 1) * lazy[index];
            if (left != right) {
                lazy[index * 2 + 1] += lazy[index];
                lazy[index * 2 + 2] += lazy[index];
            }
            lazy[index] = 0;
        }
    }

    public:
    void init(int arrSize) {
        delete[] STree;
        size = 1;
        while (size < arrSize)
            size <<= 2;
        STree = new int[size * 2 - 1];
        lazy = new int[size * 2 - 1];
        for (int i = 0; i < size * 2 - 1; i++) {
            STree[i] = lazy[i] = 0;
        }
    }
    void reset() {
        for (int i = 0; i < size * 2 - 1; i++) {
            STree[i] = lazy[i] = 0;
        }
    }
    void update(int i, int value) { updateInternal(0, 0, size - 1, i, value); }
    void updateSection(int start, int end, int value) {
        updateSectionInternal(0, value, 0, size - 1, start, end);
    }
    int getSumOfSection(int start, int end) {
        return getSumOfSectionInternal(0, 0, size - 1, start, end);
    }
    int getSize() { return size; }
    void print() {
        for (int i = 0; i < size * 2 + 1; ++i) {
            cout << STree[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    SegmentTree stree;
    stree.init(1000000);
    // cout << stree.getSize() << endl;
    int a[] = {1, 1, 1, 1, 1, 1, 1, 1};
    for (int i = 0; i < 1000000; i++) {
        stree.update(i, 1);
    }
    stree.updateSection(1, 4, 1);

    stree.updateSection(1, 100000, 1);
    stree.update(1, 1);

    cout << stree.getSumOfSection(0, 4) << endl;
    cout << stree.getSumOfSection(0, 15) << endl;
    cout << stree.getSumOfSection(0, 1000) << endl;
    return 0;
}