#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



double* Initialisation(size_t lenX)
{
	
	double* res = malloc(sizeof(int)*lenX*2);
	srand(2);
	for (size_t i = 0; i < lenX;i++)
		{	
			double tmp = rand();
			printf("tmp : %f\n",tmp);
			printf("res %zu : %f\n",i,(tmp/10));
			*(res+i) = (tmp/(double)10);
			printf("W init : %f\n",res[i]);
		}
	printf("RES : %d\n",res[0]);
	return res;
}



double*  modele(double* X, double* W,double b,size_t lenXW)
{
	double *Z = calloc(0,sizeof(int)*lenXW);
	double *A = calloc(0,sizeof(int)*lenXW);
	int j =0;
	for(size_t i = 0;i < lenXW;i++)
	{
		Z[i] = X[j * lenXW + i] * W[j * lenXW + i] + X[(j+1)*lenXW + i]* W[(j+1)*lenXW +i] + b;
	}
	for(size_t y = 0; y < lenXW;y++)
	{


		A[y] = 1/(1+exp(-(Z[y])));
	}
	//peut etre penser à free(Z) peut etre pas mal mais à voir,
	//je le met au cas-où
	free(Z);
	return A;
}