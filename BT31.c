#include<stdio.h>
#include<malloc.h>
#include<conio.h>

void nhap(int *a,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("a[%d]=",i);
		scanf("%d",(a+i));
	}
}
void xuat(int *a,int n)
{
	int i;
	for(i=0;i<n;i++)
	printf("%d ",*(a+i));
}
void hoanvi(int *a,int *b)
{
	int t;
	t=*a;
	*a=*b;
	*b=t;
}
int ktcp(int n)
{
	int i,d=0;
	for(i=1;i<=n;i++)
	if(n==i*i)
	d++;
	return d;
}
void sapxep(int *a,int n)
{
	int i,j;
	for (i=0;i<n-1;i++)
		for (j=i+1;j<n;j++)	
		{
		if(*(a+i)<*(a+j)&&ktcp(*(a+i))==1&&ktcp(*(a+j))==1)
		hoanvi(a+i,a+j);
		}
}
void don(int*a,int n)       
{
	int i,j,t;
	for (i=0;i<n;i++)
	if (ktcp(*(a+i))==1)
	{
		t=*(a+i);
		for(j=i;j>=0;j--)
		*(a+j)=*(a+j-1);
		*(a+0)=t;
	}
}
int dem_so_chan(int *a,int n)
{
	int i;
	int dem=0;
	for (i=0;i<n;i++)
	if(*(a+i) % 2 ==0)
		dem++;
	return dem;
}
main()
{
int a,n;
do
{
	printf("Nhap so phan tu cua mang: ");
	scanf("%d",&n);
}
while(n>50||n<1);
a=(int*)malloc(n*sizeof(int));
nhap(a,n);
printf("Mang vua nhap la: ");
xuat(a,n);
don(a,n);
sapxep(a,n);
printf("\nMang sau khi sap xep la: ");
xuat(a,n);
printf("\nTrong mang co %d so chan! ",dem_so_chan(a,n));
printf("\n");
getch();
}