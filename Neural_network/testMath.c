#include "math_tool.h"
#include "Neuronal_link.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
size_t len(char s[])
{
	size_t res = 0;
	for(int i = 0; s[i] != '\0'; i++)
	{
		res += 1;
	}
}

double ch_to_db(char s[])
{
	double res = 0;
	for(int i = 0; s[i] != '\0'; i++)
	{
		res = res * 10 + (s[i] - 48);
	}
	return res;
}

void ach_to_adb(char s[], double res[], size_t len)
{
	
	for(size_t i = 0; i < len; i++)
	{
		res[i] = ch_to_db(s[i]);
	}
}

void test_sum(char** argv)
{
	printf("Sum : %.2f\n",sum(argv[2], argv[3], argv[4]));
}

void test_logloss(char** argv)
{
	size_t l1 = len(argv[2]);
	size_t l2 = len(argv[3]);
	size_t l3 = len(argv[4]);
	double r1[l1] = {0};
	double r2[l2] = {0};
	double r3[l3] = {0};
	ach_to_db(argv[2],res1,l1);
	ach_to_db(argv[3],res2,l2);
	ach_to_db(argv[4],res3,l3);

	printf("Logloss : %.2f\n", logloss(r1, r2, r3);
}

void test_perceptron(char** argv)
{
	printf("Perceptron : %.2f\n",perceptron(ch_to_db(argv[2]),ch_to_db(argv[3]),ch_to_db(argv[4]),ch_to_db(argv[5]),ch_to_db(argv[6])));
}

void test_sigmoide(char** argv)
{
	printf("Sigmoide : %.2f\n",sigmoide(ch_to_db(argv[2])));
}*/

double te[] = {1,2,3}; 
double Y22[] = {0.56,0.78,1.98};
double A2[] ={0.4,0.67,0.156};

double X[2][5] = {{1,1,0,0,1},{1,0,1,0,0}};
double Y[] = {0,1,1,0,1};

int main(int argc, char** argv)
{
	
	/*if(argc >= 1)
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
	printf("Somme : %f \n",sum(0,te,(size_t)3));
	printf("Logloss : %f \n",logloss(A2,Y22,3));
	
	return 0;
}
