#ifndef __MERGE_SORT
#define __MERGE_SORT

namespace c_sort {

// bottom up merge sort
template <typename T>
void merge_sort_bottom(T a[], int n) {
    T* t = new T[n];
    register int m, l, r, il, ir, i, p;
    for (p = 1; p <= n; p <<= 1) {
        for (l = 0; l < n - p; l += p << 1) {
            ir = m = l + p;
            if (m >= n) break;
            if (a[m - 1] < a[m]) continue;
            r = (m + p) > n ? n : m + p;
            for (il = l; il < r; ++il)
                t[il] = a[il];
            il = i = l;
            for (; il < m && ir < r;)
                a[i++] = (t[il] < t[ir]) ? t[il++] : t[ir++];
            for (; il < m;)
                a[i++] = t[il++];
        }
    }
}

}  // namespace sort

#endif