#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
using namespace std::chrono;

#include <sort.hpp>
using namespace c_sort;

#define SIZE 5'000'000
int Array[SIZE];

static unsigned long long seed = 5ULL;
int random(void) {
    return ((int)((seed = seed * 25214903917ULL + 11ULL) >> 16));
}

int compare(const void* a, const void* b) {
    return *((int*)a) - *((int*)b);
}

void test(void (*func)(), const char* name) {
    for (register int i = 0; i < SIZE; ++i)
        Array[i] = abs(random());

    auto st = high_resolution_clock::now();
    cout << setw(20) << left << name << ": ";

    try {
        func();  // sort
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    auto en = high_resolution_clock::now();
    double time = duration_cast<nanoseconds>(en - st).count();

    cout << fixed << time / 1e9;

    for (register int i = 1; i < SIZE; ++i)
        if (Array[i] < Array[i - 1]) {
            cout << " ERROR";
            break;
        }
    cout << endl;
}

template <typename T>
void bit_sort(T arr[], int l, int r, int m) {  // helper
    register int s = l, e = r;
    register T t;
    for (; s != e;) {
        if (arr[s] & m) {
            --e;
            t = arr[s];
            arr[s] = arr[e];
            arr[e] = t;
        } else ++s;
    }
    m >>= 1;
    if (m == 0) return;
    if (s - l > 1) bit_sort(arr, l, s, m);
    if (r - e > 1) bit_sort(arr, e, r, m);
}

template <typename T>
void bit_sort(T arr[], int size) {
    bit_sort(arr, 0, size, 1 << 30);
}

vector<int> blockSort(vector<int> arr, int blockSize) {
    vector<vector<int> > blocks;

    // Divide the input array into blocks of size blockSize
    for (int i = 0; i < arr.size(); i += blockSize) {
        vector<int> block;

        for (int j = i; j < i + blockSize && j < arr.size(); j++) {
            block.push_back(arr[j]);
        }

        // Sort each block and append it to the list of
        // sorted blocks
        sort(block.begin(), block.end());
        blocks.push_back(block);
    }

    // Merge the sorted blocks into a single sorted list
    vector<int> result;
    while (!blocks.empty()) {
        // Find the smallest element in the first block of
        // each sorted block
        int minIdx = 0;
        for (int i = 1; i < blocks.size(); i++) {
            if (blocks[i][0] < blocks[minIdx][0]) {
                minIdx = i;
            }
        }

        // Remove the smallest element and append it to the
        // result list
        result.push_back(blocks[minIdx][0]);
        blocks[minIdx].erase(blocks[minIdx].begin());

        // If the block is now empty, remove it from the
        // list of sorted blocks
        if (blocks[minIdx].empty()) {
            blocks.erase(blocks.begin() + minIdx);
        }
    }

    return result;
}

int main() {
    cout.precision(9);

    test([]() { bits_sort(Array, SIZE); }, "radix bit sort");
    test([]() { quick_sort_mid(Array, SIZE); }, "quick sort mid");
    test([]() { quick_sort_nr(Array, SIZE); }, "quick sort non-rec");
    test([]() { quick_sort(Array, 0, SIZE); }, "quick sort");
    test([]() { bit_sort(Array, SIZE); }, "bit sort");
    test([]() { qsort(Array, SIZE, sizeof(int), compare); }, "std qsort");
    test([]() { merge_sort_bottom(Array, SIZE); }, "merge sort bottom");
    test([]() { heap_sort(Array, SIZE); }, "heap sort");

    auto a = [](int a, int b) -> int { return a * b; };

    cout << a(3, 4);

    return 0;
}