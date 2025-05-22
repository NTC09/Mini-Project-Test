#include <bits/stdc++.h>
using namespace std;
  
// Driver code
int main()
{
    // Input vector
    std::set<int> v{ 10, 20, 30, 30, 30, 40, 50 };
  
    // Print vector
    std::cout << "Vector contains :";
    for (auto i : v)
        std::cout << " " << i;
    std::cout << "\n";
  
    std::set<int>::iterator low1, low2, low3;
      
    // std :: lower_bound
    low1 = v.lower_bound(30);
    low2 = v.lower_bound(35);
    low3 = v.lower_bound(55);
  
    // Printing the lower bounds
    std::cout
        << "\nlower_bound for element 30 at position : "
        << *low1;
    std::cout
        << "\nlower_bound for element 35 at position : "
        << *low2;
    if (low3 != v.end())
    std::cout
        << "\nlower_bound for element 55 at position : "
        << *low3;
  
    return 0;
}