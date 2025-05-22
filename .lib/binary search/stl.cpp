#include <algorithm>
#include <iostream>

using namespace std;
 
int main()
{
    const int haystack[] = {1, 2, 4, 6, 14, 23, 45, 66, 99, 100};
    int size = 10;
 
    for (const auto needle : {1, 4, 9})
    {
        cout << "Searching for " << needle << '\n';
        if (binary_search(haystack, haystack + size, needle))
            cout << "Found " << needle << '\n';
        else
            cout << "No dice!\n";
    }

    const int * a = lower_bound(haystack, haystack + size, 14);
    if (a != nullptr)
        cout << "Searching >= 14: " << *a << '\n'; //14

    a = upper_bound(haystack, haystack + size, 14);
    if (a != nullptr)
        cout << "Searching > 14: " << *a << '\n'; // 23
 
    return 0;
}