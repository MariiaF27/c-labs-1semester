#include<stdio.h>
#include<stdlib.h>
#include<readline/readline.h>
#include <time.h>

#define DELIM " \t"
#define PROMPT "> "
#define MAX_CHAR_SIZE 128

char *process(const char *);

int main(){
        rl_bind_key('\t', rl_insert);
        char *input = readline(PROMPT);

        while (input != NULL){
                printf("\"%s\"\n", input);
                clock_t start = clock();
                char *output = process(input);
                clock_t end = clock();
                float t = (float) (end - start) / CLOCKS_PER_SEC;
                printf("time: %f \n", t);
                printf("\"%s\"\n", output);
                free(input);
                free(output);
                input=readline(PROMPT);
        }
        return 0;
}
char *process(const char *str){
        char *s=strdup(str);
        int s_len=strlen(s);
        char *chr=calloc(MAX_CHAR_SIZE, sizeof(char));
        char *res=calloc(s_len+1, sizeof(char));
        int chr_index=0;
        while(s[chr_index]!='\0'){
                int chr_ascii=(int) s[chr_index];
                //printf("Character %d\n", chr_ascii);
        //      if(chr_ascii!=32) chr[chr_ascii]+=1;
                if(strchr(DELIM, s[chr_index])==NULL) chr[chr_ascii]+=1;
                chr_index++;
        }
        int max=0;
        for(chr_index=0; chr_index < MAX_CHAR_SIZE; chr_index++){
                        if(chr[chr_index]>chr[max]) max=chr_index;
        }
        printf("The character with the highest frequency");
        for (chr_index = 0; chr_index < MAX_CHAR_SIZE; chr_index++){
                if (chr[chr_index]==chr[max] && max!=0){
                        printf(" '%c'", chr_index);
                }
        }
        printf("\nNumber of times is occured %d\n", chr[max]);
        int len=0;
        char *word=strtok(s, DELIM);
        while(word !=NULL){
                printf("Word: \"%s\"\n", word);
                int w_len =strlen(word);
                int j=0;
                for(int i=0; i<=w_len; i++){
                        int res_ascii= (int) word[i];
                        if(chr[res_ascii] != chr[max]){
                                word[j]=word[i];
                                j++;
                        }
                }
                w_len = strlen(word);
                if(w_len>0){
                        memcpy(res+len, word, w_len *sizeof(char));
                        len+=w_len;
                        res[len]=' ';
                        ++len;
                }
                word=strtok(NULL, DELIM);
        }
        if(len>0) --len;
        res[len]='\0';

        res=realloc(res, (len+1)*sizeof(char));

        free(s);
        free(chr);
        return res;
}