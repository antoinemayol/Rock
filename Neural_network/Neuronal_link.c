#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



void Initialisation(double **X,size_t lenX, double W[][2])
{
	srand(1);
	for (int y = 0; y < 2;y++)
	{
		for (size_t i = 0; i < lenX;i++)
		{	
			W[y][i] = rand()%10;
			//printf("W init : %f\n",W[y][i]);
		}
	}
	
}



void  modele(double **X, double **W,double b,size_t lenXW,double A[])
{
	double Z[] = {0};
	int j =0;
	for(size_t i = 0;i < lenXW;i++)
	{
		Z[i] = X[j][i]*W[j][i] + X[j+1][i]*W[j+1][i] + b;
	}
	for(size_t y = 0; y < lenXW;y++)
	{
		A[y] = 1/(1-exp(Z[y]));
	}	
}
