#include <stdio.h>
#include <string.h>
#include <math.h>
int lt(int x, int y)
{
    int out=1;
    while(y)
    {
        out*=x;
        y--;
    }
    return out;
}
void main()
{
    int i= 0,z=1,x=0;
    char data[10]={};
    char t;
    while(lt(2,i)<=z)
    i++;
    i--;
    while(i+1)
	{
		if(z<lt(2,i))
            strcat(data,"0");
        else
        {
            strcat(data,"1");
            z=z-lt(2,i);
        } 
		i--;
	}
    printf("%s",&data[0]);
}