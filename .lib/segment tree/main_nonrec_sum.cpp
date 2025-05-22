#include <iostream>

using namespace std;

#define SIZE 100
#define SEGM SIZE << 1

/* easy switch to min or max */
#define combine(a, b) ((a) + (b))

int array[SIZE];
int n = SIZE;

int segment[SEGM];
int lazy[SEGM];
int height = 0;

void init() {
    for (int t = n - 1; t > 1; t >>= 1) ++height;
    for (int i = 0; i < SEGM; ++i) {
        segment[i] = 0;
        lazy[i] = 0;
    }
}

void build() {
    for (int i = n - 1; i > 0; --i)
        segment[i] = combine(segment[i << 1], segment[i << 1 | 1]);
}

void calc(int i, int range) {
    if (lazy[i] == 0) segment[i] = combine(segment[i << 1], segment[i << 1 | 1]);
    else segment[i] += lazy[i] * range;
}

void build(int l, int r) {
    int range = 2;
    for (l += n, r += n - 1; l > 1; range <<= 1) {
        l >>= 1, r >>= 1;
        for (int i = r; i >= l; --i) calc(i, range);
    }
}

void apply(int i, int change, int range) {
    segment[i] += change * range;
    if (i < n) lazy[i] = change;
}

void push(int l, int r) {
    int s = height, range = 1 << (height - 1);
    for (l += n, r += n - 1; s > 0; --s, range >>= 1) {
        for (int i = l >> s; i <= r >> s; ++i) if (lazy[i] != 0) {
            apply(i << 1    , lazy[i], range);
            apply(i << 1 | 1, lazy[i], range);
            lazy[i] = 0;
        }
    }
}

void update(int i, int value) {
    segment[i] = value;
    for (i += n; i >>= 1;)
        segment[i] = combine(segment[i << 1], segment[i << 1 | 1]);
}

void modify__(int l, int r, int change) {
    push(l, l + 1);
    push(r - 1, r);
    int l0 = l, r0 = r, range = 1;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1, range <<= 1) {
        if (l & 1) apply(l++, change, range);
        if (r & 1) apply(--r, change, range);
    }
    build(l0, l0 + 1);
    build(r0 - 1, r0);
}

void modify(int l, int r, int change) {
    int range = 1, cl = 0, cr = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1, range <<= 1) {
        if (cl) calc(l - 1, range);
        if (cr) calc(r, range);
        if (l & 1) apply(l++, change, range), cl = 1;
        if (r & 1) apply(--r, change, range), cr = 1;
    }
    for (--l; r > 0; l >>= 1, r >>= 1, range <<= 1) {
        if (cl) calc(l, range);
        if (cr && (!cl || l != r)) calc(r, range);
    }

}

int query(int l, int r) {
    int res = 0;
    push(l, l + 1);
    push(r - 1, r);
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = combine(res, segment[l++]);
        if (r & 1) res = combine(res, segment[--r]);
    }
    return res;
}

int main() {
    init();
    for (int i = 0; i < n; ++i) {
        segment[i + n] = 10;
    }
    build();

    modify(0, 10, -1);

    cout << height << endl;
    cout << query(0, 10);

    return 0;
}