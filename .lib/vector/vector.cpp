#include <iostream>
#include <vector>

using namespace std;

struct testClass {
    int value;
};

template <typename subClass>
class Vectors {
   private:
    int __cap;
    int __size;
    subClass* __data;

   public:
    Vectors() {
        __size = 0;
        __cap = 10;
        __data = new subClass[10];
    }
    void clear() {
        __size = 0;
        if (__cap > 10) {
            __cap = 10;
            delete[] __data;
            __data = new subClass[10];
        }
    }
    void insert(subClass nSubClass) {
        if (__size >= __cap) {
            append();
        }
        __data[__size++] = nSubClass;
    }
    void append() {
        __cap *= 10;
        subClass* t = new subClass[__cap];
        for (int i = 0; i < __size; i++)
            t[i] = __data[i];
        delete[] __data;
        __data = t;
    }
    void copy(Vectors<subClass>& v1) {
        while (__cap < v1.__cap)
            append();
        for (register int i = 0; i < v1.__size; i++)
            __data[i] = v1.__data[i];
    } // replace 
    subClass& operator[](int i) { return this->__data[i]; }
    subClass pop() { return __data[--__size]; }
    bool empty() { return __size == 0; }
    int size() { return this->__size; }
};

int main() {
    Vectors<testClass> mv;
    vector<vector<testClass>> vt;
    vt.push_back({{1}});
    cout << vt[0][0].value;
    testClass t;
    cout << "Created" << endl;
    t.value = 100;
    mv.insert(t);
    t.value = 10;
    mv.insert(t);
    mv[0].value = 999;
    cout << mv[0].value << endl;
    cout << mv[1].value << endl;
    Vectors<int> Intx;
    Intx[0] = 9;
    cout << Intx[0];
    return 0;
}