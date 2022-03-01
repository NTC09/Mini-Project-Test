#include <iostream>

using namespace std;

int int_check(double a);

void float_to_fraction(double a)
{
    double i=0;
    while(int_check(a*i)==1 && i<10000)
        i++;
    cout<<a*i<<"/"<<i<<endl;
}
int int_check(double a)
{
    //int check=a/1;
    if(a==(int)a)
        return 1;
    else
        return 0;
}
int main()
{
    double a=0.25;
    double i=0;
    a=5/3;
    if(int_check(a)==0)
        cout<<"Phan so"<<endl;
    else    
        cout<<"So TN"<<endl;
    while(int_check(a*i)==0 && i<10000)
    {
        i++;
    }
    cout<<a*i<<"/"<<i<<endl;
    return 0;
}