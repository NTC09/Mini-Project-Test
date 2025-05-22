#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct a {
    int value;
    int room[1000];
    bool operator<(const a &b) const {
        return value < b.value;
    }
}aa[100000];

int main() {
    vector<a> t;
    vector<int> room;
    string a1 = "12", a2 = "34";
    a1 < a2;
    t.clear();
    for (int i = 0; i < 10; ++i) {
        t.push_back({rand() % 100});
    }
    cout << t[0].value << endl;
    t.pop_back();
    sort(t.begin(), t.end());
    for (int i = 0; i < 10; ++i) {
        cout << t[i].value << " ";
    }
    
    return 0;
}