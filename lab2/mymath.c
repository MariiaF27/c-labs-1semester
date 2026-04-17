#include<stdio.h>

int input_int(int *m)
{
	int c, status;
	char b;
	while((c=scanf("%d", m))!=1 || (b=getchar())!='\n'){
		if(c == EOF){
			printf("EOF\n");
			status = 3;
			return status;
		}
		if(c==0 || b!=1){
			printf("Incorect input\n");
			status=1;
			scanf("%*[^\n]");
			return status;
		}
	}
	if(*m<0){
		printf("Incorect value\n");
		status = 2;
		return status;
	}
	else{
		status = 0;
		return status;
	}
}

int input_double(double *m){
	int c, status;
	char b;
	while((c=scanf("%lf", m))!=1 || (b=getchar())!='\n'){
		if(c == EOF){
			printf("EOF\n");
			status = 3;
			return status;
		}
		if(c==0 || b!=1){
			printf("Incorect input\n");
			status=1;
			scanf("%*[^\n]");
			return status;
		}
	}
	if(*m<0){
		printf("Incorect value\n");
		status = 2;
		return status;
	}
	else{
		status = 0;
		return status;
	}
}

