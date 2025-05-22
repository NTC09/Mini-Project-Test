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
    }  // replace
    subClass& operator[](int i) { return this->__data[i]; }
    subClass pop() { return __data[--__size]; }
    bool empty() { return __size == 0; }
    int size() { return this->__size; }
};