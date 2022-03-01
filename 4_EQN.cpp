#include "iostream"
#include "iomanip"
#include "cmath"

using namespace std;

float R1=10000;
float R2=99077.3;
float R3=56141.6;
float R4=19993.4;

float T[4]={25,-20,-10,10};

float a[4][5],x[4]; 

int main()
{
    int n,i,j,k;
    cout.precision(16);        //set precision
    //cout.setf(ios::fixed);
    cout<<"\nEnter the no. of equations\n";        
    //cin>>n;                //input the no. of equations
    n=4;
           //declare an array to store the elements of augmented-matrix    
    //cout<<"\nEnter the elements of the augmented-matrix row-wise:\n";
    /*for (i=0;i<n;i++)
        for (j=0;j<=n;j++)    
            cin>>a[i][j];    //input the elements of array
    */
    for (j=0;j<=n;j++)    
        a[0][j]=pow(log(R1),j);
    for (j=0;j<=n;j++)    
        a[1][j]=pow(log(R2),j);
    for (j=0;j<=n;j++)    
        a[2][j]=pow(log(R3),j);
    for (j=0;j<=n;j++)    
        a[3][j]=pow(log(R4),j);
    for (j=0;j<=n;j++)    
        a[j][4]=1/(T[j]+273.15);

    for (i=0;i<n;i++)                    //Pivotisation
        for (k=i+1;k<n;k++)
            if (abs(a[i][i])<abs(a[k][i]))
                for (j=0;j<=n;j++)
                {
                    double temp=a[i][j];
                    a[i][j]=a[k][j];
                    a[k][j]=temp;
                }
    cout<<"\nThe matrix after Pivotisation is:\n";
    for (i=0;i<n;i++)            //print the new matrix
    {
        for (j=0;j<=n;j++)
            cout<<a[i][j]<<setw(16);
        cout<<"\n";
    }    
    for (i=0;i<n-1;i++)            //loop to perform the gauss elimination
        for (k=i+1;k<n;k++)
            {
                double t=a[k][i]/a[i][i];
                for (j=0;j<=n;j++)
                    a[k][j]=a[k][j]-t*a[i][j];    //make the elements below the pivot elements equal to zero or elimnate the variables
            }
     
    cout<<"\n\nThe matrix after gauss-elimination is as follows:\n";
    for (i=0;i<n;i++)            //print the new matrix
    {
        for (j=0;j<=n;j++)
            cout<<a[i][j]<<setw(16);
        cout<<"\n";
    }
    for (i=n-1;i>=0;i--)                //back-substitution
    {                        //x is an array whose values correspond to the values of x,y,z..
        x[i]=a[i][n];                //make the variable to be calculated equal to the rhs of the last equation
        for (j=i+1;j<n;j++)
            if (j!=i)            //then subtract all the lhs values except the coefficient of the variable whose value                                   is being calculated
                x[i]=x[i]-a[i][j]*x[j];
        x[i]=x[i]/a[i][i];            //now finally divide the rhs by the coefficient of the variable to be calculated
    }
    cout<<"\nThe values of the variables are as follows:\n";
    for (i=0;i<n;i++)
        cout<<x[i]<<endl;            // Print the values of x, y,z,....    
    cout<<"\nHex form:\n";
     for (i=0;i<n;i++)
        printf("0x%X\n",*((int*)&x[i]));
    return 0;
}