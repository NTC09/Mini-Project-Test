#include <iostream>

using namespace std;

class BigInteger {
    typedef unsigned long long u64;

   private:
    u64* digits;
    u64 digitLength;
    u64 capacity;

    BigInteger() {
        digits = new u64[2];
        digitLength = 0;
        capacity = 2;
    }

    BigInteger(char* src) {
        char* t = src;
        u64 len = 0;
        while (*t++)
            ++len;
        ::BigInteger(src, len);
    }

    BigInteger(char* src, u64 len) {
    }

    void extend() {
        capacity = capacity < (1 << 10) ? capacity * 2 : capacity + (1 << 10);
        u64* t = new u64[capacity];
        for (int i = 0; i < digitLength; ++i) {
            t[i] = digits[i];
        }
        delete digits;
        digits = t;
    }

   public:
    friend BigInteger operator+(BigInteger& i1, BigInteger& i2) {
    }

    friend BigInteger operator-(BigInteger& i1, BigInteger& i2) {
    }

    friend BigInteger operator*(BigInteger& i1, BigInteger& i2) {
    }

    friend BigInteger operator/(BigInteger& i1, BigInteger& i2) {
    }
};

int main() {
    return 0;
}