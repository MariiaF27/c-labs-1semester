
#ifndef ARRAY_H
#define ARRAY_H

typedef enum Err{
    Err_ok=0,
    Err_mem=-1,
} Err;

Err array_print(const int *arr, const int len, const int *arr2, const int len2);
Err array_init(int **arr, const int len);
Err array_insert(int **arr, int *len, int k, int h);
Err array_delete(int **arr, int *len, int k);
Err array_main(int **arr, int *len, int **arr2, int *len2);

#endif