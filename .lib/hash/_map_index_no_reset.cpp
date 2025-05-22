#include <iostream>
using namespace std;
#define HASH_SIZE 100
#define KEY_PUSH (1ULL << 58)
#define MASK32 0x7FFFFFFF
#define MASK32U 0xFFFFFFFFU

typedef unsigned long long u64;

u64 nullKey = KEY_PUSH;

struct Node {
    u64 key;
    int value;
    int next;
};


unsigned long long hashf(char* key) {
    register long long h = 0;
    for (register int i = 0; key[i]; i++) {
        h <<= 5;
        h ^= key[i];
    }
    return h;
}

unsigned long long hashF(char* key) {
    register long long h = 0;
    for (; *key;++key) {
        h = (h << 5) ^ *key;
    }
    return h;
}

int main(){
    Node a = {123, 1, 0},
        b = {223, 2, 0};
    int n = 0;
    for (u64 i = KEY_PUSH; i >= KEY_PUSH; i += KEY_PUSH, ++n)
        cout << n << "~" << i << endl;

    return 0;
}