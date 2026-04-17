#include<stdio.h>
#include<stdlib.h>

size_t mystrlen(const char *s){
        int res=0;
        while(*s){
                ++s, ++res;
        }
        return res;
}
void *mymemcpy(void *dest, void *src, int n){
        char *char_dest=(char *) dest;
        char *char_src=(char *) src;
        for(int i=0; i<n; i++)
                char_dest[i]=char_src[i];
                //*char_dest++=*char_src++;
        return dest;
}
char *mystrchr(const char *str, int c){
        while(*str!='\0'){
                if (*str==c) return (char*) str;
                str++;
        }
        return NULL;
}
char *mystrtok(char *str, const char *delim){
        static char *next_token=NULL;
        char *word;
        if(str != NULL){
                next_token =str;
        }
        if(next_token==NULL) return NULL;
        while (*next_token){
                if(mystrchr(delim, *next_token)==NULL)
                        break;
                next_token++;
        }
        if(*next_token == '\0') return NULL;
        word = next_token;
        while(*next_token){
                if(mystrchr(delim, *next_token)!=NULL)
                        break;
                next_token++;
        }
        if(*next_token){
                *next_token = '\0';
                next_token++;
        }
        return word;
}

char *get_str(char *prompt){
        char buf[81]={0};
        char *res=NULL;
        int len =0;
        int n=0;

        do{
                printf("%s", prompt);
                n = scanf("%80[^\n]", buf);
                if(n<0){
                        if(!res){
                                return NULL;
                        }
                }
                else if(n>0){
                        int chunk_len = mystrlen(buf);
                        int str_len = len + chunk_len;
                        res=realloc(res, str_len +1);
                        mymemcpy(res+len, buf, chunk_len);
                        len= str_len;
                }
                else{
                        scanf("%*c");
                }
        } while(n>0);
        if(len>0) res[len]='\0';
        else res = calloc(1, sizeof(char));
        return res;
}
char *mystrdup(const char *string){
        char *str;
        char *p;
        int len = mystrlen(string);
        str = malloc (len+1);
        p= str;
        while(*string) *p++=*string++;
        *p='\0';
        return str;
}