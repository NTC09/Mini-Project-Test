#include <iostream>

using namespace std;

const unsigned int Z = 1e9 + 7;
int M;

void multiple(long long a[100][100], long long t[100][100])
{
    for (int i=0; i<M; i++)
        for(int j=0; j<M; j++)
        {
        	long long temp=0;
       		for (int k=0; k<M; k++)
            {
                temp+= (a[i][k] * t[k][j])%Z;
            }
            a[i][j]=temp%Z;
		}
    cout<<"done"<<endl;
}

void power(long long a[100][100],unsigned long long n)
{
    if(n==0 || n==1) return;
    long long t[100][100];
    for(int i=0;i<M;i++)
		for(int j=0;j<M;j++)
			t[i][j]=a[i][j];
    if(n==2) multiple(a,t);
    power(a,n/2);
    multiple(a,a);
    if(n%2!=0)
        multiple(a,t);
}

int main()
{
    unsigned long long N;
    long long a[100][100];   
    cin>>M>>N;
    for (int i=0; i<M ; i++)
    {
        for (int j=0; j<M ; j++)
        {
            cin>> a[i][j];
        }
    }
    power(a,N);
    //Result
    for(int i=0;i<M;i++)
    {
        for (int j=0;j<M;j++)
            cout <<a[i][j]<<" ";
        cout <<endl;
    }
    return 0;
}