#include <stdio.h>
void clear_data(char* data)
{
	int i;
	for(i=0;i<sizeof(data);i++)
		data[i]=NULL;
}
void main()
{   
    unsigned char data_rx[100];
    sprintf(&data_rx[0],"Nut Up vua duoc nhan!\n");
    printf("%s\n",data_rx);
    clear_data(&data_rx);
    printf("-%s",data_rx);
}