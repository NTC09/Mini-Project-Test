#include <iostream>
#include <vector>

using namespace std;

#define R 1000000000LL

class BigInt {
   public:
    char* digit;
    int length;
    int capacity;
    BigInt() {
        digit = new char[10];
        length = 0;
        capacity = 10;
        digit[0] = 0;
    }
    BigInt(const char* value) {
        digit = new char[10];
        length = 0;
        capacity = 10;
        digit[0] = 0;
        convert(value);
    }
    BigInt(long long value) {
        digit = new char[10];
        length = 0;
        capacity = 10;
        digit[0] = 0;
        convert(value);
    }
    void append() {
        capacity *= 2;
        char* temp = new char[capacity];
        int i = 0;
        for (; i < length; i++)
            temp[i] = digit[i];
        for (; i < capacity; i++)
            temp[i] = 0;
        delete[] digit;
        digit = temp;
    }
    void append(int newSize) {
        while (capacity < newSize)
            append();
    }
    void convert(long long value) {  //
        int c = 0;
        int d[20];
        while (value) {
            d[c++] = value % 10;
            value /= 10;
        }
        while (capacity < c)
            append();
        length = 0;
        for (; length < c; length++)
            digit[length] = d[length];
    }
    void convert(BigInt b) {
        for (int i = 0; i < b.length; i++) {
            operator[](i) = b.digit[i];
        }
    }
    void convert(const char* value) {
        length = 0;
        while (value[length] <= '9' && value[length] >= '0') {
            operator[](length) = value[length] - '0';
            length++;
        }
        for (int i = 0; i < length / 2; i++) {
            char t = digit[i];
            digit[i] = digit[length - i - 1];
            digit[length - i - 1] = t;
        }
    }
    void mtp10() {
        for (int i = length; i > 0; --i) {
            operator[](i) = digit[i - 1];
        }
        digit[0] = 0;
        length++;
    }
    void validate() {
        while (digit[length - 1] == 0 && length > 1)
            length--;
    }
    char& operator[](int index) {
        while (index >= capacity)
            this->append();
        return this->digit[index];
    }
    friend ostream& operator<<(ostream& ou, BigInt b) {
        int i = b.length - 1;
        while (i >= 0)
            ou << (int)(b.digit[i--]);
        // ou << "; len: " << b.length << "; cap: " << b.capacity;
        return ou;
    }
    // compare
    bool operator==(const BigInt& a) const {
        if (this->length != a.length)
            return false;
        for (int i = 0; i < length; ++i) {
            if (digit[i] != a.digit[i])
                return false;
        }
        return true;
    }
    bool operator==(const long long n) const {
        BigInt a(n);
        if (this->length != a.length)
            return false;
        for (int i = 0; i < length; ++i) {
            if (digit[i] != a.digit[i])
                return false;
        }
        return true;
    }
    bool operator!=(const BigInt& a) const {
        if (this->length != a.length)
            return true;
        for (int i = 0; i < length; ++i) {
            if (digit[i] != a.digit[i])
                return true;
        }
        return false;
    }
    bool operator>(const BigInt& a) const {
        if (this->length != a.length)
            return this->length > a.length;
        for (int i = length - 1; i >= 0; --i) {
            if (digit[i] < a.digit[i])
                return false;
        }
        return true;
    }
    bool operator<(const BigInt& a) const {
        if (this->length != a.length)
            return this->length < a.length;
        for (int i = length - 1; i >= 0; --i) {
            if (digit[i] < a.digit[i])
                return true;
        }
        return false;
    }

    // arithmetic
    friend BigInt operator+(const BigInt& a, const BigInt& b) {
        BigInt result;
        result.length = 0;
        int remember = 0;
        int sum;
        while (true) {
            sum = 0;
            if (result.length < a.length)
                sum += a.digit[result.length];
            if (result.length < b.length)
                sum += b.digit[result.length];
            sum += remember;
            result[result.length++] = sum % 10;
            remember = sum / 10;
            if (result.length >= a.length && result.length >= b.length) {
                if (remember)
                    result[result.length++] = remember;
                break;
            }
        }
        result.validate();
        return result;
    }
    friend BigInt& operator+=(BigInt& a, const BigInt& b) {
        a = a + b;
        return a;
    }
    friend BigInt operator+(BigInt& a, const char& b) {
        BigInt result;
        result.convert((long long)b);
        return result + a;
    }
    friend BigInt operator*(const BigInt& a, const char& b) {
        return a * BigInt(b);
    }

    friend BigInt& operator-=(BigInt& a, const BigInt& b) {
        a = a + b;
        return a;
    }
    friend BigInt operator*(const BigInt& a, const BigInt& b) {  // pass
        BigInt result;
        result.append(a.length + b.length + 1);
        result.length = a.length + b.length;
        int* d = new int[result.length];
        for (int i = 0; i < result.length; i++) {
            d[i] = 0;
        }
        for (int i = 0; i < a.length; i++) {
            for (int j = 0; j < b.length; j++) {
                d[i + j] += a.digit[i] * b.digit[j];
            }
        }
        for (int s, i = 0, t = 0; i < result.length; ++i) {
            s = t + d[i];
            d[i] = s % 10;
            t = s / 10;
            result.digit[i] = d[i];
        }
        result.validate();
        return result;
    }
    BigInt operator*(long long a) {
        return *this * BigInt(a);
    }
    BigInt operator*=(const BigInt& a) {
        BigInt result = (*this) * a;
        return result;
    }
    BigInt operator*=(long long a) {
        return *this * BigInt(a);
    }
    friend BigInt operator/(const BigInt& a, const BigInt& b) {  // copy
        if (b == 0)
            throw("Arithmetic Error: Division By 0");

        BigInt result;
        int i, lgcat = 0, cc;
        int n = a.length, m = b.length;
        vector<int> cat(n, 0);

        for (i = n - 1; result * 10 + a.digit[i] < b; i--) {
            result *= 10;
            result += a.digit[i];
        }
        for (; i >= 0; i--) {
            result = result * 10 + a.digit[i];
            for (cc = 9; cc * b > result; cc--)
                ;
            result -= cc * b;
            cat[lgcat++] = cc;
        }
        result.length = cat.size();
        for (i = 0; i < lgcat; i++)
            result.digit[i] = cat[lgcat - i - 1];
        result.length = lgcat;
        result.validate();
        return result;
    }
    friend BigInt operator/(const BigInt& a, long long b) {
        BigInt result = a / BigInt(b);
        result.validate();
        return result;
    }

    friend BigInt power(const BigInt& a, const BigInt& b) {
        if (b == BigInt("0"))
            return BigInt("1");
        if (b == BigInt("1"))
            return a;
        BigInt p = power(a, b / 2);
        if (b.digit[0] % 2 == 0)
            return p * p;
        return a * p * p;
    }
};
char temp1[1001], temp2[1001];
int main() {
    BigInt a, b;
    unsigned long long x = 9999999999,
                       y = 9999999999;
    char* m = "123456789123456789";
    // a = 100;
    // cout << a << endl;
    /*fflush(stdin);
    gets(temp1);
    fflush(stdin);
    gets(temp2);
    a.convert(temp1);,
    b.convert(temp2);*/
    a.convert("111111111111111111111");
    b.convert(x);
    cout << a << " * " << a << " = " << endl
         << a * a << endl;
    cout << x * y << endl;
    return 0;
}