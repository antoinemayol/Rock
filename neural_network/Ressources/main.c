#include "Neuronal_link.h"
#include "math_tool.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>





int main ()
{
	
	double X[8] = {1,1,0,0,1,0,1,0};
	double Y[5] = {0,1,1,0};
	double learning_rate = 0.1;
	double loss[5] = {0,0,0,0,0} ;
	double b = 3;
	double *W = Initialisation(8);
	
	for (size_t n = 0; n < 5 ;n++)
	{
		double *A = modele(X,W,b,4);
		printf("");
		loss[n] = logloss(A,Y,4);
		double gradient = (A,Y,X,4);
		update(&gradient,&b,W,learning_rate,4);
	}

	for(int y = 0; y <5;y++)
	{
		printf("%u : %f\n",y,loss[y]);
	}

	
	


}

