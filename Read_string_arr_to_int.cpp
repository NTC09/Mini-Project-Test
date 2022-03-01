// Read_string_arr_to_int.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
	char Data[]="10 20 50 100 170";
	int Ar[5];
	int li = 0;
	for (int ki = 0; ki < 5; ki++)
	{
		int count = 0;
		while (Data[li] != ' ' && li < sizeof(Data)-1)
		{
			li++;
			count++;
		}
		std::cout << count<<"\n";
		Ar[ki] = 0;
		for (int i = 0; i < count; i++)
		{
			Ar[ki] += pow(10, i) * (Data[li-i-1]-48);
		}
		while (Data[li] < 48 && li < sizeof(Data))
		li++;
	}
	for (int ki = 0; ki < 5; ki++)
		std::cout << "Ar[" << ki << "]= " << Ar[ki] << "\n";
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
