#include<stdio.h>

#define LEN 41

int main()
{
    char str[LEN];
    char *ptr;
    int digit=0;
    int i,j,k,key;

    printf("please input a string:\n");
    ptr = fgets(str,LEN,stdin);

    i=0;j=0;k=0;
    key=1;
    while(ptr != NULL)
    {
         if((*ptr < '0') || (*ptr > '9'))
        {

            ptr++;
            key = 0;
            continue;
        }
        digit=digit*10+(*ptr-'0');
        ptr++;


    }
    printf("the number is %d\n",digit);


    return 0;
}
