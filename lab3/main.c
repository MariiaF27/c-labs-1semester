#include<stdio.h>
#include <stdlib.h>
#include "array.h"
#include "case.h"
int main()
{
    int *data=NULL, *data2=NULL;
    int len=0, len2=0;
    int option =-1;
    do {
        printf("\n");
        printf("***** MENU *****\n");
        printf("0. Exit\n");
        printf("1. Print array\n");
        printf("2. Array init\n");
        printf("3. Array insert\n");
        printf("4. Array delete\n");
        printf("5. Main solution\n");
        printf("\n");
        int r=scanf("%d", &option);
        if(r==EOF)
        {
            free(data);
            free(data2);
            return 0;
        }
        switch (option) {
            case 0:
                case0();
                break;
            case 1:
                case1(data, len, data2, len2);
                break;
            case 2:
                case2(&data, &len);
                case1(data, len, data2, len2);
                break;
            case 3:
                case3(&data, &len);
                case1(data, len, data2, len2);
                break;
            case 4:
                case4(&data, &len);
                case1(data, len, data2, len2);
                break;
            case 5:
                case5(&data, &len, &data2, &len2);
                case1(data, len, data2, len2);
                break;
            default:
                def();
                break;
        }
    } while(option!=0);
    free(data);
    free(data2);
    return 0;
}