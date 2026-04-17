#include<stdio.h>
#ifndef POINT_H
#define POINT_H

typedef struct{
    char *x;
    int y, z;
} Point;

int getName(FILE* inFileDesc, char** pStr, Point* p, int isBinary);
void putName(Point* p, FILE* outFileDesc, int isBinary);


#endif