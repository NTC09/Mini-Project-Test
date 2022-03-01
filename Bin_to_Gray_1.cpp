// Bin_to_Gray_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
int lt_b2(int n)
{
	int ra = 1, k;
	for (k = 0; k < n; k++)
		ra *= 2;
	//printf("%d\n", ra);
	return ra;
}
int main()
{
    //cout << "Hello World!\n";
	int i;
	int gray[256];
	gray[0] = 0;
	gray[1] = 1;
	for (i = 2; i < 256; i++)
	{
		int dem = 1;
		int j = i;
		while (j != 0x01)
		{
			j >>= 1;
			dem++;
		}
		int high =lt_b2(dem) - 1;
		gray[i] = gray[high - i] + lt_b2(dem - 1);
		printf("%d\n", gray[i]);
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
