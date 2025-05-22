#include <iostream>

using namespace std;

int ratio = 10;

int a[100];
int s[10];

int cal(int start, int ends) {
    int sum = 0;
    /*if (start % ratio == 0)
        i1--;
    if ((ends + 1) % ratio == 0)
        i2++;

    for (int i = start; i % ratio != 0; i++)
        sum += a[i];

    for (int i = i1; i <= i2; i++)
        sum += s[i];

    for (int i = i2 * ratio; i <= ends; i++)
        sum += a[i]; */

    for (int i = start; i <= ends; i++) {
        if ((i % ratio == 0) && ((i + ratio - 1) <= ends)) {
            sum += s[i / ratio];
            i += ratio - 1;
        }
        else
            sum += a[i];
    }

    return sum;
}

int main() {
    int sum = 0;

    for (int i = 0; i < 10; i++) {
        s[i] = 0;
    }

    for (int i = 0; i < 100; i++) {
        a[i] = rand() % 50;
        s[i / ratio] += a[i];
        if (i <= 89 && i >= 5)
            sum += a[i];
    }

    cout << cal(5, 89) << endl;

    cout << sum;
    return 0;
}