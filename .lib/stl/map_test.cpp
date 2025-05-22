#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include <map>

using namespace std;

struct st {
    int value;
    /*bool operator<(const st& b) const {
        return value < b.value;
    }*/
} ss[100];
int Count = 0;

int main() {
    unordered_map<int, st> map1;
    unordered_map<string, int> map2;

    map1[13456] = ss[Count++];

    map1.insert(make_pair(1234, ss[1]));

    st sss = map1[13456];

    map2["abc"] = 100;

    map2.insert(make_pair("abx", 199));

    map2.erase("abx");

    auto it = map2.find("abc");

    if (it != map2.end()) {
        string t = "aaa";
        it->first = t;
        it->second = 199;
    }

    map2.clear();

    unordered_map<string, st*> map3;
    map3["1234"] = &ss[0];

    st* st0 = map3["abc"];
    st0->value;

    auto it3 = map3.find("abc");

    it3->second->value = 0;
    ss[1].value;

    unordered_map<string, int> map4;
    int i = map4["111"];
    ss[i];

    return 0;
}