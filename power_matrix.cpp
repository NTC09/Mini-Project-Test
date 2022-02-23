#include <iostream>

using namespace std;

const unsigned int Z = 1e9 + 7;
int m;

class matrix{
private:
    long long **a;
    unsigned int n; //Row
    unsigned int m; //Colum
public:
    friend istream& operator>> (istream& in, matrix &x);
    matrix operator * (matrix x);
    matrix operator ^ (unsigned long long n);
    friend ostream& operator<< (ostream& ou, matrix x);
    unsigned int geta(int i, int j) { return this->a[i][j]; };
};
ostream& operator<< (ostream& ou, matrix x)
{
    for(int i=0;i<x.n;i++)
    {
        for (int j=0;j<x.m;j++)
            ou <<x.a[i][j]<<" ";
        cout <<endl;
    }
    return ou;
}
istream& operator>> (istream& in, matrix &x)
{
    x.m=x.n=m;
    x.a=new long long*[x.n];
    for (int i=0; i<x.n ; i++)
        x.a[i]=new long long[x.m];
    for (int i=0; i<x.n ; i++)
    {
        for (int j=0; j<x.m ; j++)
        {
            cin>> x.a[i][j];
        }
        cin.ignore();
    }
    return in;
}
matrix matrix::operator ^ (unsigned long long n)
{
    
    matrix t;
	t.m=this->n;  
	t.n=this->m;
	t.a=new long long *[2];
    for (int i=0; i<t.n ; i++)
       	t.a[i]=new long long [t.m];
    for(int i=0;i<t.n;i++)
		for(int j=0;j<t.m;j++)
			t.a[i][j]=this->a[i][j];
    if(n==1) return t;
    if(n%2==0)
        t=(t^(n/2)) * (t^(n/2));
    else 
        t=t*(((t^(n/2)) * (t^(n/2))));
    return t;
}

matrix matrix::operator * (matrix x)
{
    matrix t;
	t.m=x.m;
	t.n=this->n;
	t.a=new long long*[t.n];
    for (int i=0; i<t.n ; i++)
       	t.a[i]=new long long[t.m];
    for (int i=0; i<t.n; i++)
        for(int j=0; j<t.m; j++){
        	t.a[i][j]=0;
       		for (int k=0; k<x.n; k++){
                t.a[i][j]+= (this->a[i][k]* x.a[k][j])%Z;
			}
            t.a[i][j]%=Z;
		}
	return t;
}
int main()
{
    unsigned long long n;   
    matrix a;
    cin>>m>>n;
    cin>>a;
    a=a^n;
    cout<<a;
    return 0;
}