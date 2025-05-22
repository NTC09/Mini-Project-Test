#include <iostream>

using namespace std;

#define SIZE 16
#define SEGM SIZE << 1

/* easy switch to min or sum */
#define combine(a, b) (((a) < (b)) ? (b) : (a))
#define lefts(i) (i << 1)
#define right(i) (i << 1 | 1)
#define update_sm(i) segment[i] = combine(segment[lefts(i)], segment[right(i)])

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

void build() {
    for (int i = n - 1; i > 0; --i) {
        update_sm(i);
    }
}

void update(int i, int value) {
    segment[i] = value;
    for (i += n; i >>= 1;)
        update_sm(i);
}

void calc(int p) {
    if (lazy[p]) segment[p] += lazy[p];
    else update_sm(p);
}

#define lazy_add(p, c) lazy[c] += lazy[p], segment[c] += lazy[p];
void down(int p) {
    int s = height;
    for (p += n; s > 0; --s) {
        int i = p >> s;
        if (lazy[i]) {
            int li = lefts(i), ri = right(i);
            lazy_add(i, li);
            lazy_add(i, ri);
            lazy[i] = 0;
        }
    }
}

void modify(int l, int r, int change) {
    down(l);
    down(r - 1);
    l += n, r += n;
    int l0 = l, r0 = r - 1, up_l = 0, up_r = 0;
    for (; l < r; l >>= 1, r >>= 1) {
        if (up_l) calc(l - 1);
        if (up_r) calc(r);
        if (l & 1) segment[l] += change, lazy[l++] += change, up_l = 1;
        if (r & 1) segment[--r] += change, lazy[r] += change, up_r = 1;
    }
    for (--l; r > 0; l >>= 1, r >>= 1) {
        if (up_l) calc(l);
        if (up_r && (!up_l || l != r)) calc(r);
    }
}

int query(int l, int r) {
    down(l);
    down(r - 1);
    int res = -2e9;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) if (res < segment[l++]) res = segment[l - 1];
        if (r & 1) if (res < segment[--r]) res = segment[r];
    }
    return res;
}

int main() {
    init();
    for (int i = 0; i < n; ++i) {
        segment[i + n] = 10 * i + 10;
    }
    build();

    modify(3, 15, 100);
    modify(5, 11, 20);
    modify(0, 8, 30);

    cout << height << endl;
    cout << query(5, 11) << endl;
    cout << query(7, 16) << endl;

    for (int i = 0; i < n - 1; ++i)
        down(i);
    cout << query(5, 11) << endl;
    cout << query(7, 16) << endl;
    return 0;
}