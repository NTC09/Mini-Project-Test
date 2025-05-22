#include <iostream>
using namespace std;

template <typename TYPE>
class MinHeap {
#define SIZE 1000000
   private:
    TYPE* data;
    int size;
    void heapifyUp(int index) {
        register int newIndex = index, 
            parent = (newIndex - 1) / 2;
        if (parent >= 0 && comp(parent, newIndex))
                newIndex = parent;
        if (newIndex != index) {
            swap(newIndex, index);
            heapifyUp(newIndex);
        }
    }
    void heapify(int index) {
        register int newIndex = index,
            left = 2 * newIndex + 1, 
            right = 2 * newIndex + 2;
        if (left < size && comp(newIndex, left))
                newIndex = left;
        if (right < size && comp(newIndex, right))
                newIndex = right;
        if (newIndex != index) {
            swap(newIndex, index);
            heapify(newIndex);
        }
    }
    void swap(int newIndex, int index) {
        register TYPE t = data[newIndex];
        data[newIndex] = data[index];
        data[index] = t;
    }
    bool comp(int i1, int i2) { 
        return (data[i1] < data[i2]); 
    }

   public:
    MinHeap() {
        clear();
        data = new TYPE[SIZE];
    }
    void clear() { size = 0; }
    void push(TYPE t) {
        data[size] = t;
        heapifyUp(size++);
    }
    TYPE pop() {
        swap(0, --size);
        heapify(0);
        return data[size];
    }
    TYPE top() {
        if (size == 0)
            return TYPE();
        return data[0];
    }
    bool isEmpty() { return size == 0; }
};

#include <iostream>
using namespace std;

int main() {
    // test
    MinHeap<int> m;

    for (int i = 0; i < 1000000; i++)
        m.push(rand());

    int prev = 0x7FFFFFFF, cur = 0x7FFFFFFF;
    while (!m.isEmpty()) {
        prev = cur;
        cur = m.pop();
        if (cur > prev) {
            cout << "fail" << endl;
            break;
        }
    }
    if (m.isEmpty())
        cout << "pass" << endl;
    return 0;
}