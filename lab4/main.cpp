#include<stdio.h>
#include<string.h>
#include<readline/readline.h>
#define DELIM "  \t"
#define PROMPT "> "

int main(){
    int max, n, i ,x, count[80];
    char chr[80];
    printf("Enter a string:");
    char *str=readline(PROMPT);
    n=strlen(str);
    chr[0]=str[0];
    count[0]=1;
    x=0;
    for(i=1; i<n; i++){
        int j;
        for(j=0; j<=x, j++){
            if(str[i]==chr[j]) count[j]++;
        }
        if(i>=J){
            x++;
            chr{}
        }
    }
}