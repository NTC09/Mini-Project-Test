// TheMatrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <cmath>
#include <windows.h>
#include <conio.h>

using namespace std;
//=======================================================================
int one(int a)
{
    if (a % 2 == 0) return 1;
    return -1;
}
//=======================================================================
class matrix {
private:
    double** a;
    unsigned int n; //Hang
    unsigned int m; //Cot
public:
    friend istream& operator>> (istream& in, matrix& x);
    friend ostream& operator<< (ostream& ou, matrix x);
    matrix operator + (matrix x);
    matrix operator - (matrix x);
    matrix operator * (matrix x);
    matrix operator ++ ();//Chua lam
    matrix operator -- ();//Chua lam
    matrix operator ! ();//MA tran nghich dao
    matrix operator ~ ();//Ma tran chuyen vi
    double det();
    friend void Dao2Cot(matrix& x, int p, int q);//Dao vi tri 2 cot
    friend void Dao2Hang(matrix& x, int p, int q);//Dao vi tri 2 hang
    int getn() { return this->n; };
    int getm() { return this->m; };
    double geta(int i, int j) { return this->a[i][j]; };
    friend double Det(matrix A) { return A.det(); };
    void nhapB(matrix A);
    void nhapB_nhan(matrix A);
};
istream& operator>> (istream& in, matrix& x)
{
    cout << "Nhap so hang :"; in >> x.n;
    cout << "Nhap so cot: "; in >> x.m;
    x.a = new double* [x.n];
    for (int i = 0; i < x.n; i++)
        x.a[i] = new double[x.m];
    for (int i = 0; i < x.n; i++)
        for (int j = 0; j < x.m; j++)
        {
            cout << "a[" << i << "," << j << "]="; cin >> x.a[i][j];
        }
    return in;
}
void matrix::nhapB(matrix A)
{
    this->n = A.getn();
    this->m = A.getm();
    a = new double* [n];
    for (int i = 0; i < n; i++)
        a[i] = new double[m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            cout << "a[" << i << "," << j << "]="; cin >> a[i][j];
        }
}
void matrix::nhapB_nhan(matrix A)
{
    this->n = A.getm();
    this->m = A.getn();
    a = new double* [n];
    for (int i = 0; i < n; i++)
        a[i] = new double[m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            cout << "a[" << i << "," << j << "]="; cin >> a[i][j];
        }
}
ostream& operator<< (ostream& ou, matrix x)
{
    for (int i = 0; i < x.n; i++)
    {
        for (int j = 0; j < x.m; j++)
            ou << setw(10) << x.a[i][j] << " ";
        cout << endl;
    }
    return ou;
}
matrix matrix::operator+(matrix x)
{
    matrix t;
    if (this->m != x.m || this->n != x.n) {
        cout << "Hai mang khong cung kich thuoc.";
        t.m = 1;
        t.n = 1;
        t.a = new double* [t.n];
        for (int i = 0; i < t.n; i++)
            t.a[i] = new double[t.m];
        t.a[0][0] = 0;
        return t;
    }
    else {
        t.m = x.m;
        t.n = x.n;
        t.a = new double* [t.n];
        for (int i = 0; i < t.n; i++)
            t.a[i] = new double[t.m];
        //=========================
        for (int i = 0; i < x.n; i++)
            for (int j = 0; j < x.m; j++)
                t.a[i][j] = this->a[i][j] + x.a[i][j];
    }
    return t;
    //Work
}
matrix matrix::operator-(matrix x)
{
    matrix t;
    if (this->m != x.m || this->n != x.n) {
        cout << "Hai mang khong cung kich thuoc.";
        t.m = 1;
        t.n = 1;
        t.a = new double* [t.n];
        for (int i = 0; i < t.n; i++)
            t.a[i] = new double[t.m];
        t.a[0][0] = 0;
        return t;
    }
    else {
        t.m = x.m;
        t.n = x.n;
        t.a = new double* [t.n];
        for (int i = 0; i < t.n; i++)
            t.a[i] = new double[t.m];
        //=========================
        for (int i = 0; i < x.n; i++)
            for (int j = 0; j < x.m; j++)
                t.a[i][j] = this->a[i][j] - x.a[i][j];
    }
    return t;
    //Work
}
matrix matrix::operator*(matrix x)
{
    matrix t;
    if (this->m != x.n) {
        //cout<<"Hai ma tran khong the nhan"<<endl;
        t.m = 1;
        t.n = 1;
        t.a = new double* [t.n];
        for (int i = 0; i < t.n; i++)
            t.a[i] = new double[t.m];
        t.a[0][0] = 0;
        return t;
    }
    t.m = x.m;
    t.n = this->n;
    t.a = new double* [t.n];
    for (int i = 0; i < t.n; i++)
        t.a[i] = new double[t.m];

    for (int i = 0; i < t.n; i++)
        for (int j = 0; j < t.m; j++) {
            t.a[i][j] = 0;
            for (int k = 0; k < x.n; k++) {
                t.a[i][j] += this->a[i][k] * x.a[k][j];
            }
        }
    return t;
    //Work
}
matrix matrix::operator ~()
{
    matrix x;
    x.m = this->n;
    x.n = this->m;
    x.a = new double* [x.n];
    for (int i = 0; i < x.n; i++)
        x.a[i] = new double[x.m];
    for (int i = 0; i < x.n; i++)
        for (int j = 0; j < x.m; j++)
            x.a[i][j] = this->a[j][i];
    return x;
}
matrix matrix::operator !()
{
    if (this->m != this->n || this->det() == 0)
    {
        //cout<<"\nKhong ton tai nghich dao"<<endl;
        matrix t;
        t.m = 1;
        t.n = 1;
        t.a = new double* [t.n];
        for (int i = 0; i < t.n; i++)
            t.a[i] = new double[t.m];
        t.a[0][0] = 0;
        return t;
    }
    //Ma tran phu hop y'
    matrix x;
    x.m = this->n;
    x.n = this->m;
    x.a = new double* [x.n];
    for (int i = 0; i < x.n; i++)
        x.a[i] = new double[x.m];
    for (int i = 0; i < x.n; i++)
        for (int j = 0; j < x.m; j++)
            x.a[i][j] = this->geta(i, j);
    double _det = 1 / this->det();
    matrix y = ~x;
    for (int i = 0; i < y.n; i++)
        for (int j = 0; j < y.m; j++)
        {
            //cout<<"\nKhong ton tai nghich dao"<<endl;
            matrix t;
            t.m = x.n - 1;
            t.n = x.m - 1;
            t.a = new double* [t.n];
            for (int z = 0; z < t.n; z++)
                t.a[z] = new double[t.m];
            matrix x;
            x.m = this->n;
            x.n = this->m;
            x.a = new double* [x.n];
            for (int i = 0; i < x.n; i++)
                x.a[i] = new double[x.m];
            for (int i = 0; i < x.n; i++)
                for (int j = 0; j < x.m; j++)
                    x.a[i][j] = this->geta(i, j);
            int l = i, k = j;
            while (l < x.n - 1)
            {
                Dao2Cot(x, l, l + 1);
                l++;
            }
            while (k < x.m - 1)
            {
                Dao2Hang(x, k, k + 1);
                k++;
            }
            for (int p = 0; p < t.n; p++)
                for (int q = 0; q < t.m; q++)
                    t.a[p][q] = x.a[p][q];
            y.a[i][j] = Det(t);
        }
    for (int i = 0; i < y.n; i++)
        for (int j = 0; j < y.m; j++)
            y.a[i][j] = y.a[i][j] * one(i + j) * _det;
    return y;
}
void Dao2Cot(matrix& x, int k, int l)
{
    for (int i = 0; i < x.n; i++)
        swap(x.a[i][l], x.a[i][k]);
}
void Dao2Hang(matrix& x, int k, int l)
{
    for (int i = 0; i < x.m; i++)
        swap(x.a[l][i], x.a[k][i]);
}
double matrix::det()
{
    double _det = 1;
    double** x;
    int m = this->getm();
    int n = this->getn();
    x = new double* [n];
    for (int i = 0; i < n; i++)
        x[i] = new double[m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            x[i][j] = this->geta(i, j);
        }
    //Kiem tra ma tran co vuong khong
    if (m != n) {
        //cout<<"\nKhong ton tai dinh thuc"<<endl;
        //return NULL;
        exit(0);
    }
    if (m == 1)//Ma tran cap 1
        return x[0][0];
    if (m == 2)//Ma tran cap 2
        return x[0][0] * x[1][1] - x[1][0] * x[0][1];
    //===========================
    /*int k=-1;
    do
    {
        k++;
        if(x[0][k]!=0)
            break;
    }
    while(k<m);//Kiem tra hang dau tien xem co toan so 0 khong
    //============================x[0][0] != 0
    if (k>=m)
        return 0;
    if (k>0)
    {
        for (int i=0;i<n;i++)
            swap(x[i][0],x[i][k]);
        _det=_det*-1;
    }*/
    //============================
    int f = 0;
    while (f < n - 1)
    {
        int j = f;
        while (x[f][j] == 0 && j < n)
        {
            j++;
            _det = _det * -1;
        }
        if (j == n)
            return 0;
        if (j > f)
            for (int i = 0; i < n; i++)
                swap(x[i][f], x[i][j]);
        //============================
        for (int k = f + 1; k < n; k++)
        {
            double h = x[f][k] / x[f][f];
            for (int i = 0; i < n; i++)
                x[i][k] = x[i][k] - x[i][f] * h;
        }
        _det = _det * x[f][f];
        f++;
    }
    _det = _det * x[f][f];
    return _det;
}
int main()
{
    matrix A, B, C;
    int choice = -1;
    while (1)
    {
        cout << "0. Exit" << endl;
        cout << "1. Cong hai ma tran" << endl;
        cout << "2. Tru hai ma tran" << endl;
        cout << "3. Nhan hai ma tran" << endl;
        cout << "4. Tim ma tran chuyen vi" << endl;
        cout << "5. Tim ma tran nghich dao" << endl;
        cout << "6. Tinh dinh thuc" << endl;
        while (choice < 0 || choice >6)
        {
            cout << "Nhap lua chon: ";
            cin >> choice;
        }
        switch (choice)
        {
        case 0:
            cout << "Chuong trinh ket thuc sau 5 giay..." << endl;
            Sleep(5000);
            return 0;
            break;
        case 1:
            cout << "Nhap ma tran A: " << endl;
            cin >> A;
            cout << "Nhap ma tran B: " << endl;
            B.nhapB(A);
            cout << "A = " << endl << A;
            cout << "B= " << endl << B;
            C = A + B;
            cout << "C=A+B " << endl << C << endl;
            break;
        case 2:
            cout << "Nhap ma tran A: " << endl;
            cin >> A;
            cout << "Nhap ma tran B: " << endl;
            B.nhapB(A);
            cout << "A = " << endl << A;
            cout << "B= " << endl << B;
            C = A - B;
            cout << "C=A-B " << endl << C << endl;
            break;
        case 3:
            cout << "Nhap ma tran A: " << endl;
            cin >> A;
            cout << "Nhap ma tran B: " << endl;
            B.nhapB_nhan(A);
            cout << "A = " << endl << A;
            cout << "B= " << endl << B;
            C = A * B;
            cout << "C=A*B " << endl << C << endl;
            break;
        case 4:
            cout << "Nhap ma tran A: " << endl;
            cin >> A;
            cout << "A = " << endl << A;
            B = ~A;
            cout << "Ma tran chuyen vi cua A:" << endl << B;
            break;
        case 5:
            cout << "Nhap ma tran A: " << endl;
            cin >> A;
            cout << "A = " << endl << A;
            B = !A;
            cout << "Ma tran nghich dao cua A:" << endl << B;
            break;
        case 6:
            cout << "Nhap ma tran A: " << endl;
            cin >> A;
            cout << "A = " << endl << A;
            cout << "Dinh thuc cua A: det(A)= " << setprecision(10) << Det(A) << endl;
            break;
        }
        choice = -1;
        cout << "Nhan phim bat ky de tiep tuc..." << endl;
        _getch();
    }
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
