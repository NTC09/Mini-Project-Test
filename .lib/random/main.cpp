#include <iostream>

using namespace std;

namespace Random {
long long seed = 1;
long long* point_seed;
void init() {
    intmax_t _seed;
    delete point_seed;
    point_seed = new long long;
    _seed = reinterpret_cast<intmax_t>(point_seed);
    seed = _seed;
    cout << seed << "\t";
}
int rand_int() {
    init();
    seed >>= rand() % 7;
    seed = seed * rand();
    return seed;
}
unsigned int rand_uint() {
    unsigned int t = rand_int();
    //cout << t << endl;
    return seed;
}
long long rand_long() {
    init();
    seed = (-1) * (seed & 0x7FF) + seed + rand();
    seed = (seed & 0x8000) ? -seed : seed;
    return seed;
}
}  // namespace Random

int dupl[100] = {0};
int t,d;

int main() {
    for (int i = 0; i < 100; i++) {
        t = Random::rand_int() % 100;
        dupl[t]++;
        if (dupl[t] > 1)
            d++;
        cout << t << endl;
    }
    cout << "Duplicate:" << d;
    return 0;
}