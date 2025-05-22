#ifndef __QUICK_SORT
#define __QUICK_SORT

namespace c_sort {

template <typename T>
void quick_sort(T input[], register int first, register int last) {
    register int pivot, i, j;
    register T temp;
    if (first < last) {
        pivot = first;
        i = first;
        j = last;
        while (i < j) {
            while (input[i] <= input[pivot] && i < last)
                i++;
            while (input[j] > input[pivot])
                j--;
            if (i < j) {
                temp = input[i];
                input[i] = input[j];
                input[j] = temp;
            }
        }
        temp = input[pivot];
        input[pivot] = input[j];
        input[j] = temp;
        quick_sort(input, first, j - 1);
        quick_sort(input, j + 1, last);
    }
}

/*============================================================================*/
#define __c_swap(a, b) \
    t = a;             \
    a = b;             \
    b = t;

#define __partition(arr, l, h)        \
    x = arr[h];                       \
    i = (l - 1);                      \
    for (j = l; j <= h - 1; j++) {    \
        if (arr[j] <= x) {            \
            ++i;                      \
            __c_swap(arr[i], arr[j]); \
        }                             \
    }                                 \
    __c_swap(arr[i + 1], arr[h]);     \
    p = (i + 1);

template <typename type>
void quick_sort_nr(type arr[], int size) {
    int* stack = new int[size];
    register int top = -1, p, i, j, h, l;
    register type t, x;
    stack[++top] = 0;
    stack[++top] = size - 1;
    while (top >= 0) {
        h = stack[top--];
        l = stack[top--];
        __partition(arr, l, h);
        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }
}

template <typename type>
void quick_sort_mid(type arr[], int size) {
    register int s = -1, i = 0, j = size, l, r;
    register type t, p;
    while (j) ++i, j >>=1;
    int st[i * 4];
    st[++s] = 0, st[++s] = size - 1;
    while (s >= 0) {
        r = st[s--], l = st[s--];
        p = arr[l + (r - l) / 2];
        j = r, i = l;
        while (1) {
            while (i <= j && arr[i] < p) ++i;
            while (i <= j && arr[j] > p) --j;
            if (i <= j) {
                t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
                ++i, --j;
            } else break;
        }
        if (i < r) st[++s] = i, st[++s] = r;
        if (l < j) st[++s] = l, st[++s] = j;
    }
}

/*============================================================================*/


}  // namespace c_sort

#endif