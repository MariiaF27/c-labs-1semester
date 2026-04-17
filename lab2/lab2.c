#include<stdio.h>
#include<math.h>
#include"mymath.h"

double root_n (double a, int n, int m)
{
	double y0=a;
	double y1=(1./n)*((n-1)*y0+a/pow(y0, n-1));
	int i;
	for(i=1; i<=m-1; i++)
	{
		y0=y1;
		y1=(1./n)*((n-1)*y0+a/pow(y0, n-1));
	}
	return y1;
}
int main()
{
	double a;
	int n, m;
	int status;
	printf("Enter a: \n");
	do status = input_double(&a), printf("Status: %d\n", status);
	while(status!=0 && status!=3);
	if(status==3) return 0;
	printf("Enter n: \n");
	do status = input_int(&n), printf("Status: %d\n", status);
	while(status!=0 && status!=3);
	if(status==3) return 0;
	printf("Enter m: \n");
	do status = input_int(&m), printf("Status: %d\n", status);
	while(status!=0 && status!=3);
	if(status==3) return 0;
	double y1=root_n(a, n, m);
	double y2=pow(a, 1./n);
	printf("y1: %.16f\ny2: %.16f\n", y1, y2);
	return 0;
}
