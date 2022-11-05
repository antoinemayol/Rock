#include <math.h>
#include "Neuronal_link.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

double sum(int s_index, double list[], size_t len)
{
	double res = 0;
	printf("JE SUIS PASSER");
	for(long unsigned int i = s_index; i < len; i++)
	{
		res += list[i];
	}
	return res;
}

double logloss(double as[], double ys[], size_t m)
{
	double res = 0;
	for(long unsigned int i = 0; i < m; i++)
	{
		/*printf("tmp : %f\n",res);
		printf("log(as[i]) : %f\n",log(as[i]));
		printf("ys[i] : %f\n",ys[i]);
		printf("log(1 - as[i]) : %f\n",log(1-as[i]));
		printf("1 - ys[i]) : %f\n\n",(1-ys[i]));*/
		res = res + ys[i] * log(as[i]) + (1-ys[i]) * log(1 - as[i]);
	}

	return (res / m) * 1;
}

double perceptron(double x1, double x2, double b, double w1, double w2)
{
	return (w1 * x1) + (w2 * x2) + b;
}

double sigmoide(double z)
{
	return 1 / 1 + exp(-z);
}

double* gradient(double *A, double *Y,double *x,size_t len)
{
	double *res = calloc(0,sizeof(int)*3);
	size_t i = 0;
	while (i < len)
	{
		*res += *(x+i) * (*(A + i )- *(Y + i)); 
		*(res + 1) += x[len + i] * (*(A+i)-*(Y+i));
		*(res+2) += ( *(A+i) - *(Y+i));
		i+=1;
		if (i >= len)
		{
			*res = *res * (1/len);
			*(res+1) = *(res+1) * (1/len);
		}

	}
	return res;
}

void update(double* res,double* b,double* W, double learning_rate,size_t len)
{
	for(size_t i =0; i<2;i++)
	{
		for(size_t y = 0 ; y < len;y++)
		{
			*(W+y) -= (learning_rate * *(res+i)); 
			
		}
	}
	*b = learning_rate * *(res+2);
}





