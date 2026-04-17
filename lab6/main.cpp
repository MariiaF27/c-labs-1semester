#include <stdio.h>
#include"list.h"

int input(List *list){
    printf("Input some words (empty line to finish):\n");
    int letter = getchar();
    int is_empty_line = 1;

    while (letter != EOF){
        while(letter==' ' || letter =='\t'){
            letter = getchar();
        }

        while(letter!='\n' && letter != EOF){
            list_put(list, letter);
            is_empty_line=0;
            letter = getchar();
        }


        if(is_empty_line){
            break;
        }

        if(letter=='\n'){
            list_put(list, '\n');
        }
        is_empty_line=1;
        letter=getchar();

    }
}






int main(){

    List *list = list_new();
    int check=input(list);
    int N;
    printf("Enter N");
    scanf("%d", &N);

    while (getchar()!='\n');
    while(check!=EOF){
        printf("Initialiized list:\n");
        list_print(list);

        printf("New list:\n");
        process(list);
        process2(list, N);
        list_print(list);

        list_delete(list);
        list=list_new();
        check=input(list);
    }

    list_delete(list);
    return 0;
}