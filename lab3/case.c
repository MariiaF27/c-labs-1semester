#include<stdio.h>
#include<stdlib.h>
#include"array.h"
#include"mymath.h"

int case0(){
    printf("Exiting...");
    return 0;
}
int case1(int *data, int len, int *data2, int len2){
    int g;
    g=array_print(data, len, data2, len2);
    if(g==-1) printf("Oops... array is empty");
    return 0;
}
int case2(int **data, int *len){
    printf("Enter length of array\n");
    input_int(len);
    int g;
    g=array_init(data, *len);
    printf("Result %d\n", g);
    return 0;
}
int case3(int **data, int *len){
    int k, h, g;
    if(*len==0) printf("Enter value to insert\n"), input_int(&h);
    if(*len!=0){
        printf("Enter value to insert\n");
        input_int(&h);
        printf("Enter position to insert\n");
        input_int(&k);
    }
    g=array_insert(data, len, k, h);
    printf("Result %d\n", g);
    return 0;
}
int case4(int **data, int *len)
{
    int d, g;
    if(*len==0) printf("First init array\n");
    else{
        printf("Enter position where to delete: \n");
        input_int(&d);
    }
    g=array_delete(data, len, d);
    printf("Result %d\n", g);
    return 0;
}
int case5(int **data, int *len, int **data2, int *len2)
{
    int g;
    g=array_main(data, len, data2, len2);
    if(g==-1) printf("First init array\n");
    printf("Result %d\n", g);
    return 0;
}
int def()
{
    printf("Wrong input\n");
    scanf("%*[^\n]");
    getchar();
    return 0;
}