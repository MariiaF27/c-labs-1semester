#include<stdio.h>

int input_int(int *m)
{
    int c, status;
    char b;
    printf("Enter input of value");
    while((c=scanf("%d", m))!=1 || (b=getchar())!='\n')
    {
        if(c == EOF)
        {
            printf("EOF\n");
            status = 3;
            return status;
        }
        if(c==0 || b!=1)
        {
            printf("Incorect input\n");
            status=1;
            scanf("%*[^\n]");
        }
        printf("Your input of value");
    }
    return 0;
}