#include <stdio.h>
#include <stdlib.h>
#include"array.h"
#include "mymath.h"

Err array_print(const int *arr, const int len, const int *arr2, const int len2){
        if (!len && !len2)      return Err_mem;
        for(int i=0; i<len; ++i) printf("array[%d] = %d\n", i, arr[i]);
        for(int i=0; i<len2; ++i) printf("subarray[%d]=%d\n", i, arr2[i]);
        return Err_ok;
}
Err array_init(int **arr, const int len){
        if(len<=0) return Err_mem;
        int *new_arr=realloc(*arr, len*sizeof(int));
        for(int i=0; i<len; i++){
                int status;
                status = input_int(&new_arr[i]);
                if (status==3){
                free(new_arr);
                return Err_ok;
                }
        }
        *arr=new_arr;
        return Err_ok;
}
Err array_insert(int **arr, int *len, int k, int h){
        if(*len==0) k=1;
        if(k<0) return Err_mem;
        int new_len=*len+1;
        int *new_arr=realloc(*arr, new_len*sizeof(int));
        for(int i=*len-1; i>=k; i--) new_arr[i+1]=new_arr[i];
        if (k>*len) new_arr[new_len-1]=h;
        else new_arr[k]=h;
        *arr=new_arr;
        *len=new_len;
        return Err_ok;
}
Err array_delete(int **arr,int *len, int k){
        if(*len==0) return Err_mem;
        if(k<0 || k>=*len) return Err_mem;
        int new_len= *len -1;
        int *new_arr=realloc(*arr, *len*sizeof(int));
        for (int i=k; i<new_len; i++) new_arr[i]=new_arr[i+1];
        if(new_len!=0) new_arr=realloc(new_arr, new_len*sizeof(int));
        *arr=new_arr;
        *len=new_len;
        return Err_ok;
}
Err array_main (int **arr,int *len, int **arr2, int *len2){
        if(!(*len)) return Err_mem;
        int new_len =*len;
        int *new_arr=realloc(*arr, new_len*sizeof(int));
        int ans = new_arr[0];
        int ans_l=0, ans_r=0;
        int sum=0, minus_pos=-1;
        for (int i=0; i<*len; i++){
                sum+=new_arr[i];
                if(sum>ans){
                        ans=sum;
                        ans_l=minus_pos+1;
                        ans_r=i;
                }
                if(sum<0){
                        sum=0;
                        minus_pos=i;
                }
        }
        int k;
        k=ans_r-ans_l+1;
        *len2=k;
        int *a=malloc(k*sizeof(int));
        for(int i=0; i<k; i++) a[i]=new_arr[ans_l+i];
        *arr2=a;
        new_len=*len-k;
        for(int i=ans_l; i<*len-k; i++) new_arr[i]=new_arr[i+k];
        if(new_len!=0) new_arr=realloc(new_arr, new_len*sizeof(int));
        *arr=new_arr;
        *len=new_len;
        return Err_ok;
}

