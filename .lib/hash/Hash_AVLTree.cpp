#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

#define LL long long
#define MAX_ 100000

string gen_random(const int len) {
    static const char alpha[] = "abcdefghijklmnopqrstuvwxyz";
    string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alpha[rand() % (sizeof(alpha) - 1)];
    }

    return tmp_s;
}

map<string, int> nameList;
set<string> Set;
LL arr[MAX_];
string str[MAX_];

int main() {
    for (int i = 0; i < MAX_; i++) {
        arr[MAX_] = rand();
        str[i] = gen_random(10);
    }
    auto st = chrono::high_resolution_clock::now();
    for (int i = 0; i < MAX_; i++) {
        // nameList.insert(make_pair(str[i], arr[i]));
        Set.insert(str[i]);
    }

    /*
    nameList[gen_random(10)] = &arr[1];
    nameList[gen_random(10)] = &arr[2];
    nameList[gen_random(10)] = &arr[3];
    nameList[gen_random(10)] = &arr[4];
    nameList[gen_random(10)] = &arr[5];
    nameList[gen_random(10)] = &arr[6];
    */
    /*
     for (auto a = nameList.begin(); a != nameList.end(); a++) {
         cout << a->first << endl;
     }
     */
    auto en = chrono::high_resolution_clock::now();
    double cTime = chrono::duration_cast<chrono::nanoseconds>(en - st).count();
    cout << endl
         << cTime / 1e9;
    return 0;
}