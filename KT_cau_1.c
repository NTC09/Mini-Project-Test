#include <stdio.h>

int kiem_tra_nguyen_to(int a)
{
    int dem=0;
    for(int i=1; i<=a; i++)
        if( a%i==0 )
            dem++;
    if(dem==2) return 1;
    return 0;
}

void main()
{
    int so_1, so_2, so_3;
    int dem=0, tong=0;
    //Nhap 3 so bat ky
    printf("Nhap so thu nhat: "); scanf("%d",&so_1);
    printf("Nhap so thu hai: "); scanf("%d",&so_2);
    printf("Nhap so thu ba: "); scanf("%d",&so_3);
    //Kiem tra
    if(kiem_tra_nguyen_to(so_1)==0) 
        {
            tong+=so_1;
            dem++;
        }
    if(kiem_tra_nguyen_to(so_2)==0) 
        {
            tong+=so_2;
            dem++;
        }
    if(kiem_tra_nguyen_to(so_3)==0) 
        {
            tong+=so_3;
            dem++;
        }
    //Ket qua
    printf("\nTong cac so khong nguyen to: %d",tong);
    printf("\nTrong ba so co %d so khong nguyen to.",dem);
}