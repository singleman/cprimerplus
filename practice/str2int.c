#include<stdio.h>
#define LEN 41

int main()
{
    char str[LEN];
    char *ptr;
    int digit[LEN]={0};
    int i,j;
    int key=0;

    printf("please input a string:\n");
    ptr = fgets(str,LEN,stdin);

    i=0;
    while(*ptr != '\0')
    {
         if((*ptr < '0') || (*ptr > '9'))
        {

            ptr++;
	    key=0;
            continue;
        }
	if(key==0)
		i++;
        digit[i]=digit[i]*10+(*ptr-'0');
	key=1;
        ptr++;
    }

    j=i;
    for(i=1;i<=j;i++)
	  printf("%d number is %d\n",i,digit[i]);

    return 0;
}
