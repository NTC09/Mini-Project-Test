#include <time.h>
#include <chrono>
#include <cmath>
#include <iostream>
#include <unordered_set>
#include <set>
#include <map>
using namespace std;
#define FOR(i, start, end) for (register int i = (start); i < (end); i++)

set<char*> NameList;
map<char*,int> NameMap;

char name[11];
int nameIndex = 0;
int a[1000000] = {0};
int Max = 0;
int duplicate = 0;

unsigned int _hash(char a[11]);

void resCreateName(int count) {
    if (nameIndex == 1000000)
        return;
    if (count == 10) {
        // cout << name << endl;
        unsigned int index = _hash(name);
        if (a[index] >= 1)
            duplicate++;
        a[index]++;
        if (a[index] > Max)
            Max = a[index];
        //cout << index << endl;
        nameIndex++;
        return;
    }
    for (char x = 'a'; x <= 'z'; x++) {
        name[count] = x;
        resCreateName(count + 1);
    }
}

unsigned int _hash(char a[11]) {
    unsigned long long hash = 1;
    for (int i = 0; i < 10; i++) {
        hash <<= 5;
        hash ^= a[i];
    }
    return hash % 1000007;
}
inline bool charComp(char* a, char* b) {
    FOR(i, 0, 8) {
        if (a[i] != b[i]) {
            return false;
        }
        if (a[i] == 0 || b[i] == 0)
            break;
    }
    return true;
}
int main() {
    auto str = chrono::high_resolution_clock::now();
    int t, n = 10;
    resCreateName(0);
    for (auto a = NameList.begin(); a != NameList.end(); a++) {
        cout << *a << endl;
    }
    cout <<charComp("abbc", "abc") << endl;
    auto end = chrono::high_resolution_clock::now();
    double cTime = chrono::duration_cast<chrono::microseconds>(end - str).count();
    cout << duplicate << endl
         << Max;
    cout << endl
         << cTime / 1e6;
    return 0;
}
