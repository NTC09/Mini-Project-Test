#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

void blockSort(int arr[], int n, int blockSize) {
    // Chia mảng thành các khối và sắp xếp từng khối
    for (int i = 0; i < n; i += blockSize) {
        int end = min(i + blockSize, n);
        sort(arr + i, arr + end);
    }

    // Gộp các khối đã sắp xếp
    auto compare = [](pair<int, pair<int, int>> a,
                       pair<int, pair<int, int>> b) -> bool {
        return a.first > b.first;
    };

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,
                   decltype(compare)>
        minHeap(compare);

    for (int i = 0; i < n; i += blockSize) {
        if (i < n) {
            minHeap.push({arr[i], {i, i}});
        }
    }

    int sortedIndex = 0;
    while (!minHeap.empty()) {
        auto [val, idx] = minHeap.top();
        minHeap.pop();
        arr[sortedIndex++] = val;
        int blockIdx = idx.first;
        int elementIdx = idx.second;
        if (elementIdx + 1 < min(blockIdx + blockSize, n)) {
            minHeap.push({arr[elementIdx + 1], {blockIdx, elementIdx + 1}});
        }
    }
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int blockSize = 3;
    blockSort(arr, n, blockSize);
    cout << "Mảng đã sắp xếp: ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}