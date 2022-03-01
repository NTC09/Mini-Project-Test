#include<stdio.h>
#include<malloc.h>
#include<conio.h>

void nhap(int*a,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("a[%d]=",i);
		scanf("%d",(a+i));
	}
}
void xuat(int*a,int n)
{
	int i;
	for(i=0;i<n;i++)
	printf("%d ",*(a+i));
}
int kiem_tra_nguyen_to(int a)
{
    int dem=0;
    int i;
    for(i=1; i<=a; i++)
        if( a%i==0 )
            dem++;
    if(dem==2) return 1;
    return 0;
}
void chen(int*a,int n,int so_duoc_chen,int vi_tri)
{
	int i,j,t;
	for (i=n-1; i>vi_tri; i--)
	*(a+i)=*(a+i-1);
	*(a+vi_tri)=so_duoc_chen;
}
void hoanvi(int *a,int *b)
{
	int t;
	t=*a;
	*a=*b;
	*b=t;
}
void sapxep(int *a,int n)
{
	int i,j;
	for (i=0;i<n-1;i++)
		for (j=i+1;j<n;j++)	
		{
		    if(*(a+i)<*(a+j)&&kiem_tra_nguyen_to(*(a+i))==1&&kiem_tra_nguyen_to(*(a+j))==1)
		        hoanvi(a+i,a+j);
		}
}
void main()
{
    int *a,n=0;
    while(n>50||n<1)
    {
        printf("Nhap so phan tu cua mang: ");
        scanf("%d",&n);
    }
    a=(int*)malloc(n*sizeof(int));
    nhap(a,n);
    printf("Mang vua nhap la: ");
    xuat(a,n);
    //Sap xep
    sapxep(a,n);
    printf("\nMang sau khi sap xep la: ");
    xuat(a,n);
    //Chen 2000 vao vi tri 1
    n++;
    chen(a,n,2000,1);
    printf("\nMang sau khi chen la: ");
    xuat(a,n);
    printf("\n");
    getch();
}