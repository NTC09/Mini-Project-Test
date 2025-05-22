#include <iostream>

using namespace std;

#define SIZE 123
#define SEGM SIZE << 1

/* easy switch to min or max */


int array[SIZE];
int n = SIZE;

int segment[SEGM];
int lazy[SEGM];
int height = 1;

void init() {
    for (int t = n - 1; t > 1; t >>= 1)
        ++height;
    for (int i = 0; i < SEGM; ++i) {
        segment[i] = 0;
        lazy[i] = 0;
    }
}
int combine(int &a, int &b) {
    return ((a) > (b) ? (b) : (a));
}

void build() {
    for (int i = n - 1; i > 0; --i)
        segment[i] = combine(segment[i << 1], segment[i << 1 | 1]);
}

void calc(int i) {
    if (lazy[i] == 0)
        segment[i] = combine(segment[i << 1], segment[i << 1 | 1]);
    else segment[i] += lazy[i];
}

void build(int l, int r) {
    for (l += n, r += n - 1; l > 1;) {
        l >>= 1, r >>= 1;
        for (int i = r; i >= l; --i)
            calc(i);
    }
}

void apply(int i, int change) {
    segment[i] += change;
    if (i < n) lazy[i] = change;
}

void push(int l, int r) {
    int s = height;
    for (l += n, r += n - 1; s > 0; --s) {
        for (int i = l >> s; i <= r >> s; ++i) {
            if (lazy[i] != 0) {
                apply(i << 1, lazy[i]);
                apply(i << 1 | 1, lazy[i]);
                lazy[i] = 0;
            }
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
    int l0 = l, r0 = r;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) apply(l++, change);
        if (r & 1) apply(--r, change);
    }
    build(l0, l0 + 1);
    build(r0 - 1, r0);
}

void modify(int l, int r, int change) {
    push(l, l + 1);
    push(r - 1, r);
    int cl = 0, cr = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (cl) calc(l - 1);
        if (cr) calc(r);
        if (l & 1) apply(l++, change), cl = 1;
        if (r & 1) apply(--r, change), cr = 1;
    }
    for (--l; r > 0; l >>= 1, r >>= 1) {
        if (cl) calc(l);
        if (cr && (!cl || l != r)) calc(r);
    }
}

int query(int l, int r) {
    int res = 2e9;
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

    modify(10, 20, -2);
    modify(10, 30, -2);
    modify(12, 15, -4);
    modify(30, 40, 4);

    cout << height << endl;
    cout << query(5, 60);

    return 0;
}