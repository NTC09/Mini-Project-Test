#ifndef __RADIX_BIT_SORT
#define __RADIX_BIT_SORT

namespace c_sort {

#define BT_BITS     16                      // bit size used for sort each loop
#define BT_COUNTER  (1 << BT_BITS)          // counter array size
#define BT_MASK     (BT_COUNTER - 1)        // mask to get counter
#define BT_BITS_SIZE 32                     // full bit size of element
#define BT_LOOP_TIME (BT_BITS_SIZE / BT_BITS)


template<typename T>
void bits_sort(T arr[], int size) {
    T *arr_t = new T[size];
    int counter[BT_COUNTER];
    register int i, t, loops = 0, frag, shift;
    for (; loops < BT_LOOP_TIME; ++loops) {
        shift = loops * BT_BITS;
        for (i = 0; i < BT_COUNTER; ++i)
            counter[i] = 0;
        for (i = 0; i < size; ++i) {
            frag     = arr[i];
            arr_t[i] = frag;
            frag     = (frag >> shift) & BT_MASK;
            ++counter[frag];
        }
        t = counter[0];
        for (i = 1; i < BT_COUNTER; ++i)
            t += counter[i], counter[i] = t;
        for (i = size - 1; i >= 0; --i) {
            t         = arr_t[i];
            frag      = (t >> shift) & BT_MASK;
            frag      = --counter[frag];
            arr[frag] = t;
        }
    }
}

}  // namespace sort

#endif