#include <iostream>
#include <stdio.h>

using namespace std;

int main() {

    int arr[] = {8, 9};

    union T
    {
        int a[2];
        long long b;
    } t;

    T* arr_u = (T*)arr;

    // cout << arr_u->a[0] << endl;
    // cout << arr_u->a[1] << endl;
    // cout << arr_u->b << endl;

    t.a[0] = 0;
    t.a[1] = 0;
    t.b = (1ULL << 32) | 2ULL;

    // cout << t.b << endl;
    // cout << t.a[0] << endl;
    // cout << t.a[1] << endl;
    unsigned short xxx = 12;
    printf ("%lld", xxx);
{
    return 0;
}
}