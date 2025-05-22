#ifndef __HEAP_SORT
#define _HEAP_SORT

namespace c_sort {

#define __h_swap(a, b) \
    t = a;             \
    a = b;             \
    b = t;

#define __heapify(data, index, size)                   \
    ni = id = index;                                   \
    while (true) {                                     \
        il = (id << 1) | 1;                            \
        ir = il + 1;                                   \
        if (il < size && data[ni] < data[il]) ni = il; \
        if (ir < size && data[ni] < data[ir]) ni = ir; \
        if (id != ni) {                                \
            __h_swap(data[id], data[ni]);              \
            id = ni;                                   \
        } else {                                       \
            break;                                     \
        }                                              \
    }

template <typename T>
void heap_sort(T data[], int N) {
    register int i, id, il, ir, ni;
    register T t;
    for (i = N / 2 - 1; i >= 0; i--) {
        __heapify(data, i, N);
    }
    for (i = N - 1; i > 0; i--) {
        __h_swap(data[0], data[i]);
        __heapify(data, 0, i);
    }
}

}  // namespace sort

#endif