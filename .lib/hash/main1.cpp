#include <iostream>
#include <bitset>
#include <chrono>

using namespace std::chrono;
using namespace std;

#define ull unsigned long long

ull Hash(const char* str) {
    register ull h = 0;
    for (register int s = 54; s>0; s -= 6) {
        h |= (ull)(*str++ &0x3F);
        h <<= 6;
    }
    return h;
}

ull Hash2(const char* str) {
    register ull h = 0;
    for (register int s = 54; s > 0; s -= 6) {
        h |= *str++ - 64LL;
        h <<= 6;
    }
    return h;
}
ull hashF(const char* s) {
    ull v = 0;
    for (int i = 0; s[i]; i++)
        v = (v << 6) | (s[i] > 96 ? s[i] - 96 : s[i] - 38);
    return v;
}

ull hash1(const char* str) {
    register ull h = 0;
    while (*str) h = (h <<= 5) | (ull)(*str++ & 0x1F);
    return h;
}

int main(){
    cout << ((long long)0xFFFFF << 35) << endl;
    cout << hash1("aaaa") << endl;
    cout << hash1("aaba");
    return 0;
    double Time;
    auto en = high_resolution_clock::now();
    auto st = high_resolution_clock::now();
    for (int i = 0; i< 1e7; i++) {
        Hash("seunghyunA\0");
    }
    en = high_resolution_clock::now();
    Time = duration_cast<microseconds>(en - st).count();
    cout << Time / 1e6 << endl;

    st = high_resolution_clock::now();
    for (int i = 0; i < 1e7; i++) {
        Hash2("seunghyunA\0");
    }
    en = high_resolution_clock::now();
    Time = duration_cast<microseconds>(en - st).count();
    cout << Time / 1e6 << endl;

    bitset<64> a;
    a = Hash("aa\0");
    cout <<a << endl;
    a = Hash("Aa\0");
    cout << a << endl;
    /*
    seunghyun -100    +0
    jinpyo      -70     +100
    sangsoo     -100    +0
    dongjin     -0      +0
    heehoon*/
    cout << Hash("seunghyun\0") << endl;
    cout << hashF("seunghyun\0") << endl;
    /*cout << Hash("jinpyo\0") << endl;
    cout << Hash("sangsoo\0") << endl;
    cout << Hash("dongjin\0") << endl;
    cout << Hash("heehoon\0") << endl;*/
    return 0;
}