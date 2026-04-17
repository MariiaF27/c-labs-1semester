#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<ctype.h>
#include <readline/readline.h>
#include <time.h>
#define PROMPT "> "

typedef struct{
        char *x;
        int y, z;
} Point;

Point point_new(char *x, int y, int z){
        Point p;
        p.x=strdup(x);
        p.y=y;
        p.z=z;
        return p;
}

int trimStr(char* pStr){
        size_t len=strlen(pStr);
        char *start=pStr;
        while(isspace(*start)) start++;
        char *end=pStr+len-1;
        while(end>start && isspace(*end)) end--;
        *(end+1)='\0';
        memmove(pStr, start, end-start+2);
        return strlen(pStr);
}


int countDigits(int num){
        int count=0;
        if(num<0) num=-num;
        do {
                count++;
                num/=10;
        } while (num>0);
        return count;
}

int getName(FILE* inFileDesc, char** pStr, Point* p, int isBinary){
        static int numNames=0;
        char buffer[1024];
        char *x=NULL;
        int y=0, z=0;

        if(isBinary){
                int len;
                if(fread(&len, sizeof(int), 1, inFileDesc)!=1) return 0;

                x=malloc(len);
                if(!x) return 0;

                if(fread(x, sizeof(char), len, inFileDesc)!=(size_t)len ||
                   fread(&y, sizeof(int), 1, inFileDesc)!=1 ||
                   fread(&z, sizeof(int), 1, inFileDesc)!=1) {
                        free(x);
                        return 0;
                   }
                *p =point_new(x, y, z);
                fprintf(stderr, "Point: x=%s, y=%d, z=%d\n", x, y, z);

                return 1;
        }
        else {
        while(1){
                if(*pStr){
                        free(*pStr);
                        *pStr=NULL;
                }

                if(stdin==inFileDesc){
                        fprintf(stdout, "Organization %d: ", numNames+1);
                        char *line = readline(PROMPT);

                        *pStr=strdup(line);
                        free(line);
                } else {
                        if(fscanf(inFileDesc, "%1023[^\n]\n", buffer)!=1){
                                return 0;
                        }
                        *pStr=strdup(buffer);
                }

                trimStr(*pStr);

                if(strlen(*pStr)==0){
                        fprintf(stderr, "Empty input. Exiting.\n");
                        free(*pStr);
                        return 0;
                }


                x=strtok(*pStr, " ");
                char *y_str=strtok(NULL, " ");
                char *z_str=strtok(NULL, " ");


                if(!x || !y_str || !z_str){
                        fprintf(stderr, "Please provied data in the format: <Organization name> <INN> <Number of empoyees>\n");
                        free(*pStr);
                        *pStr=NULL;
                        continue;
                }


                char *endptr=NULL;
                y=strtol(y_str, &endptr, 10);
                if(*endptr!='\0' || countDigits(y)!=3){
                        fprintf(stderr, "Please enter an integer for the 2-nd value.\n");
                        free(*pStr);
                        *pStr=NULL;
                        continue;
                }

                z=strtol(z_str, &endptr, 10);
                if(*endptr!='\0') {
                        fprintf(stderr, "Please enter an integer for the 3-rd value.\n");
                        free(*pStr);
                        *pStr=NULL;
                        continue;
                }


                *p=point_new(x, y, z);
                numNames++;
                return 1;
        }
        }
}


void putName(Point* p, FILE* outFileDesc, int isBinary){
        if(isBinary){
                int len=strlen(p->x)+1;
                fwrite(&len, sizeof(int), 1, outFileDesc);
                fwrite(p->x, sizeof(char), len, outFileDesc);
                fwrite(&p->y, sizeof(int), 1, outFileDesc);
                fwrite(&p->z, sizeof(int), 1, outFileDesc);
        } else {
                fprintf(outFileDesc, "%s %d %d\n", p->x, p->y, p->z);
        }
}