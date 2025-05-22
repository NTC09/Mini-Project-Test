#include <iostream>

using namespace std;

#define SIZE 100
#define SEGM SIZE << 1

/* easy switch to min or sum */
#define combine(a, b) (((a) < (b)) ? (b) : (a))
#define lefts(i) (i << 1)
#define right(i) (i << 1 | 1)

int array[SIZE];
int n = SIZE;

int segment[SEGM];
int lazy[SIZE];
int height = 0;

void init() {
    for (int t = n - 1; t > 1; t >>= 1)
        ++height;
    for (int i = 0; i < SEGM; ++i)
        segment[i] = 0;
}

void build() {
    for (int i = n - 1; i > 0; --i) {
        segment[i] = combine(segment[i << 1], segment[i << 1 | 1]);
        lazy[i] = 0;
    }
}

void build(int i) {
    for (i >>= 1; i > 1; i >>= 1)
        segment[i] = combine(segment[i << 1], segment[i << 1 | 1]) + lazy[i];
}

void apply(int i, int value) {
    segment[i] += value;
    if (i < n) lazy[i] = value;
}

void push(int p) {
    for (int s = height; s > 0; --s) {
        int i = p >> s;
        if (lazy[i] != 0) {
            apply(i << 1, lazy[i]);
            apply(i << 1 | 1, lazy[i]);
            lazy[i] = 0;
        }
    }
}

void update(int i, int value) {
    segment[i] = value;
    for (i += n; i >>= 1;)
        segment[i] = combine(segment[i << 1], segment[i << 1 | 1]);
}

void modify(int l, int r, int change) {
    l += n, r += n;
    int l0 = l, r0 = r - 1;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) apply(l++, change);
        if (r & 1) apply(--r, change);
    }
    build(l0);
    build(r0);
}

int query(int l, int r) {
    int res = -2e9;
    l += n, r += n;
    push(l);
    push(r - 1);
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = combine(segment[l++], res);
        if (r & 1) res = combine(segment[--r], res);
    }
    return res;
}

int main() {
    init();
    for (int i = 0; i < n; ++i) {
        segment[i + n] = 10 * i + 10;
    }
    build();

    modify(0, 10, 1000);
    // modify(5, 10, 10000);

    modify(20, 25, 1100);

    cout << height << endl;
    cout << query(0, SIZE) << endl;

    return 0;
}