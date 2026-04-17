#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<ctype.h>
#include <readline/readline.h>
#include <time.h>
#include "point.h"
#define PROMPT "> "


int usage(char* cmd);

void binaryInsertionSort(Point* points, int n, int (*cmp)(const Point*, const Point*));
void gnomeSort(Point* points, int n, int (*cmp)(const Point*, const Point*));
void quickSort(Point* points, int n, int (*cmp)(const Point*, const Point*));

int point_cmp_x(const Point *p1, const Point *p2);
int point_cmp_x_inv(const Point *p1, const Point *p2);
int point_cmp_y(const Point *p1, const Point *p2);
int point_cmp_y_inv(const Point *p1, const Point *p2);
int point_cmp_z(const Point *p1, const Point *p2);
int point_cmp_z_inv(const Point *p1, const Point *p2);



int main(int argc, char *argv[]){
        int ch;
        FILE* inputFile=NULL;
        FILE* outputFile=NULL;
        int sortType=1;
        int fieldType=1;
        int sortDirection=1;
        int isBinaryInput=0;
        int isBinaryOutput=0;
        while((ch=getopt(argc, argv, "i:I:o:O:s:f:d:h")) != -1){
                switch(ch){
                        case 'i':
                                if(NULL == (inputFile=fopen(optarg, "r"))){
                                        fprintf(stderr, "Cannot open input file \"%s\"\n", optarg);
                                        return 1;
                                }
                                fprintf(stderr, "Using \"%s\" for input.\n", optarg);
                                break;
                        case 'I':
                                if(NULL == (inputFile=fopen(optarg, "rb"))){
                                        fprintf(stderr, "Cannot open binary input file \"%s\"\n", optarg);
                                        return 1;
                                }
                                isBinaryInput=1;
                                fprintf(stderr, "Using \"%s\" for binary input.\n", optarg);
                                break;
                        case 'o':
                                if(NULL == (outputFile=fopen(optarg, "w"))){
                                        fprintf(stderr, "Cannot open output file \"%s\"\n", optarg);
                                        return 1;
                                }
                                fprintf(stderr, "Using \"%s\" for output.\n", optarg);
                                break;
                        case 'O':
                                if(NULL == (inputFile=fopen(optarg, "wb"))){
                                        fprintf(stderr, "Cannot open binary output file \"%s\"\n", optarg);
                                        return 1;
                                }
                                isBinaryOutput=1;
                                fprintf(stderr, "Using \"%s\" for binary output.\n", optarg);
                                break;
                        case 's':
                                sortType=atoi(optarg);
                                if(sortType<1 || sortType>3){
                                        fprintf(stderr, "Invalid sort type. Use 1 for binary insertion, 2 for gnome sort, 3 to qsort\n");
                                        return 1;
                                }
                                break;
            case 'f':
                                fieldType=atoi(optarg);
                                if(fieldType<1 || fieldType>3){
                                        fprintf(stderr, "Invalid field type. Use 1 for x, 2 for y, 3 for z.\n");
                                        return 1;
                                }
                                break;
                        case 'd':
                                if(strcmp(optarg, "asc")==0){
                                        sortDirection=1;
                                } else if (strcmp(optarg, "desc")==0){
                                        sortDirection=-1;
                                } else {
                                        fprintf(stderr, "Invalid sort direction. Use 'asc' for ascending or 'desc' for descending.\n");
                                        return 1;
                                }
                                break;
                        case 'h':
                        default:
                                usage(argv[0]);
                                return 1;
                }
        }
        if(!inputFile){
                inputFile = stdin;
                fprintf(stderr, "Using stdin for input.\n");
        }
        if(!outputFile){
                outputFile=stdout;
                fprintf(stderr, "Using stdout for output.\n");
        }



        char * nameBuffer=NULL;
        Point *points = NULL;
        int pointCount=0;
        Point p;

        while(getName(inputFile, &nameBuffer, &p, isBinaryInput)){
                points=realloc(points, (pointCount+1)*sizeof(Point));
                points[pointCount++]=p;
        }

        //
        int (*cmp)(const Point*, const Point*);

        if(fieldType==1){
                if(sortDirection==1){
                        cmp=point_cmp_x;
                } else {
                        cmp=point_cmp_x_inv;
                }
                } else if (fieldType==2){
                if(sortDirection==1){
                        cmp=point_cmp_y;
                } else {
                        cmp=point_cmp_y_inv;
                }
                } else if(fieldType==3){
                        if(sortDirection == 1){
                                cmp=point_cmp_z;
                        } else {
                                cmp = point_cmp_z_inv;
                        }
                }

                //time
                clock_t t0=clock();
                if(sortType==1){
                        binaryInsertionSort(points, pointCount, cmp);
                } else if (sortType==2){
                        gnomeSort(points, pointCount, cmp);
                } else if (sortType==3){
                        quickSort(points, pointCount, cmp);
                }
                clock_t t1=clock();
                double ftime=(double)(t1-t0)/CLOCKS_PER_SEC;


                fprintf(stdout, "Sorting completed in %.6f seconds.\n", ftime);


                fprintf(stdout, "\nSorted points:\n");
                for(int i=0; i<pointCount; i++){
                        putName(&points[i], outputFile, isBinaryOutput);
                        free(points[i].x);
                }

        free(points);
        fclose(inputFile);
        fclose(outputFile);
        return 0;
}


int usage(char* cmd){
        fprintf(stderr, "usage: %s [-i inputFileName] [-o outputFileName] [-s sortType] [-f fieldType] [-d sort direction]\n", cmd);
        fprintf(stderr, "usage: %s [-I inputFileName] [-O outputFileName] - for binary files \n", cmd);
        fprintf(stderr, "If -i or -I inputFileName is not given, stdin is used.\n");
        fprintf(stderr, "If -o or -O outputFileName is not given, stdout is used.\n");
        fprintf(stderr, "Sort types: -s\n 1 - Binary Insertion Sort (default)\n 2 - Gnome Sort\n 3 - Standart Qsort\n");
        fprintf(stderr, "Field types: -f\n 1 - organization\n 2 - INN\n 3 - Number of employees\n");
        fprintf(stderr, "Sort direction:-d\n asc - Ascending\n desc - descending\n");
        return 1;
}



int point_cmp_x(const Point *p1, const Point *p2){
        return strcmp(p1->x, p2->x);
}

int point_cmp_x_inv(const Point *p1, const Point *p2){
        return strcmp(p2->x, p1->x);
}

int point_cmp_y(const Point *p1, const Point *p2){
        return p1->y - p2->y;
}

int point_cmp_y_inv(const Point *p1, const Point *p2){
        return p2->y - p1->y;
}

int point_cmp_z(const Point *p1, const Point *p2){
        return p1->z - p2->z;
}

int point_cmp_z_inv(const Point *p1, const Point *p2){
        return p2->z - p1->z;
}

void quickSort(Point* points, int n, int (*cmp)(const Point*, const Point*)){
        qsort(points,n, sizeof(Point), (int (*)(const void*, const void*))cmp);
}


void binaryInsertionSort(Point* points, int n, int (*cmp)(const Point*, const Point*)){
        for(int i=0; i<n; i++){
                Point temp=points[i];
                int left=0, right=i - 1;

                while (left<=right){
                        int mid=left+(right-left)/2;
                        if(cmp(&points[mid], &temp)>0 ){
                                right= mid-1;
                        } else {
                                left=mid+1;
                        }
                }
                for(int j=i-1; j>=left; j--){
                        points[j+1]=points[j];
                }
                points[left]=temp;
        }
}

void gnomeSort(Point* points, int n, int (*cmp)(const Point*, const Point*)){
        int index=0;

        while(index<n){
                if(index==0 || cmp(&points[index-1], &points[index])<=0){
                        index++;
                } else {
                        Point temp= points[index];
                        points[index]=points[index-1];
                        points[index-1]=temp;
                        index--;
                }
        }
}
