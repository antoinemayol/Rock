#include <math.h>
#include "Neuronal_link.h"
#include <string.h>
#include <stdio.h>

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

double gradient()
{
	
}


