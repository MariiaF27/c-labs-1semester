#include<math.h>
#include<stdio.h>
#include"mymath.h"
double root_n(double a, int n, double eps, int *count)
{
	double y0=a;
	double y1=(1./n)*((n-1)*y0+a/pow(y0, n-1));
	while(fabs(y1-y0)>eps)
	{
		y0=y1;
		y1=(1./n)*((n-1)*y0+a/pow(y0,n-1));
		(*count)++;
	}
	return y1;
}
int main()
{
	double a, eps;
	int n;
	int count;
	int status;
	printf("Enter a: \n");
	do status = input_double(&a), printf("Status: %d\n", status);
	while (status !=0 && status !=3);
	if(status==3) return 0;
	printf("Enter n: \n");
	do status = input_int(&n), printf("Status: %d\n", status);
	while (status !=0 && status !=3);
	if(status==3) return 0;
	printf("Enter eps: \n");
	do status = input_double(&eps), printf("Status: %d\n", status);
	while (status !=0 && status !=3);
	if(status==3) return 0;
	double y1=root_n(a ,n, eps, &count);
	double y2=pow(a, 1./n);
	printf("y1: %.16f\ny2: %.16f\ncount iterations: %d\n", y1, y2, count);
	return 0;
}
