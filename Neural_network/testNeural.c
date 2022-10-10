#include "math_tool.h"
#include "Neuronal_link.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double te[3] = {1,2,3}; 
double Y22[3] = {0,0,1} ;
double A2[3] ={0.4,0.67,0.156};

double X[10] = {1,1,0,0,1,1,0,1,0,0};
double Y[5] = {0,1,1,0,1};

int main(int argc, char** argv)
{	
	printf("bite");
	srand(2);
	double b = rand();
	size_t len = 5;
	double* tmp = Initialisation(len);
	printf("%f",tmp[0]);
	printf("INIT : %f \n",b);

	for(int i = 0; i<2;i++)
	{
		for(int j = 0; j < 5;j++)
		{
			printf("W_id %u : %f\n",i,tmp[j * len +i]);
		}
	}

	printf("sortie");
	double A[5] = {0};
	modele(X,tmp,b,5,A);
	for(int y = 0; y < 5;y++)
		{
			printf("A_id %u : %f\n",y,A[y]);
		}
	


	return 0;
}
