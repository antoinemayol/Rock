#include "math_tool.h"
#include "Neuronal_link.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double te[] = {1,2,3}; 
double Y22[] = {0,0,1} ;
double A2[] ={0.4,0.67,0.156};

double X[2][5] = {{1,1,0,0,1},{1,0,1,0,0}};
double Y[] = {0,1,1,0,1};

int main(int argc, char** argv)
{
/*	
	if(argc >= 1)
	{
		if(strcmp(argv[1],"--sum") == 0)
		{
			test_sum(argv);
		}

		if(strcmp(argv[1],"--logloss") == 0)
		{
			test_logloss(argv);
		}

		if(strcmp(argv[1],"--perceptron") == 0)
		{
			test_perceptron(argv);
		}

		if(strcmp(argv[1],"--perceptron") == 0)
		{
			test_sigmoide(argv);
		}
		return 0;
	}
	
	*/
	//printf("Somme : %f \n",sum(0,te,(size_t)3));
	//printf("Logloss : %f \n",logloss(A,Y,3));
	
	srand(2);
	double W[][2] = {0};
	double b = rand();
	size_t len = 5;
	Initialisation(X,len,W);
	printf("INIT : %f \n",b);

	for(int i = 0; i<2;i++)
	{
		for(int j = 0; j < 5;j++)
		{
			printf("W_id %u : %f\n",i,W[i][j]);
			printf("AVANT AVANT AVANT");
		}
	}
	printf("AVANT AVANT");
	double A[5] = {0};
	printf("AVANT");
	modele(X,W,b,5,A);
	printf("APRES");
	for(int y = 0; y < 5;y++)
		{
			printf("W_id %u : %f\n",y,A[y]);
		}
	


	return 0;
}
