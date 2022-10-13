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

int main()
{	
	printf("bite");
	srand(2);
	double b = rand();
	size_t len = 5;
	
	
	printf("INIT : %f \n",b);

	
	double w[10] = {1,4,2,6,7,8,5,9,3,1};
	printf("sortie\n");
	
	double *A = modele(X,w,b,5);
	for(int y = 0; y < 5;y++)
		{
			printf("A_id %u : %f\n",y,A[y]);
		}
	
	//si A[i] <= 1, alors on a log(1 - A[i]) = -infini
	//don faut absolument eviter ça sinon logloss marche pas
	A[0] = 0.62;
	A[1] = 0.74;

	double logl = logloss(A,Y,5);
	printf("logl : %f\n",logl);

	return 0;
}
