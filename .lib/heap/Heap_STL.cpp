#include<bits/stdc++.h> 
using namespace std;
int Size = 1000000;
int arr[1000000];
int next;

int main()
{
    auto st = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < Size;i++){
        arr[i] = rand();
    }
    make_heap(arr, arr+Size);
    auto en = chrono::high_resolution_clock::now();
    double cTime = chrono::duration_cast<chrono::nanoseconds>(en - st).count();
    cout << endl
         << cTime / 1e9;
    for (int i = 0; i < 100;i++){
        arr[Size++] = rand();
        push_heap(arr, arr + Size);
    }

    en = chrono::high_resolution_clock::now();
    cTime = chrono::duration_cast<chrono::nanoseconds>(en - st).count();
    cout << endl
         << cTime / 1e9;
    return 0;
}