#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "save_and_load.h"

double getRandom(double lower, double upper)
{
	double range = upper - lower;
	double div = RAND_MAX / range;
	return lower + (rand() / div);
}

double sig(double z)
{
	return 1 / (1 + exp(-z));
}
double Dsig(double z)
{
	return z * (1 - z);
}

void mix(int *array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

void SaveAll()
{
	
}

#define nbIn 2
#define nbHidLay 1
#define nbHidNod 2
#define nbOut 1



#define nbTest 4

int main()
{

	// INIT ARRAYS
	double pas = 0.1f;

	double *hidLay = malloc(nbHidNod * sizeof(double));
	double *outLay = malloc(nbOut * sizeof(double));

	double *hidLayBias = malloc(nbHidNod * sizeof(double));
	double *outLayBias = malloc(nbOut * sizeof(double));

	double *hidWght = malloc((nbIn * nbHidNod) * sizeof(double));
	double *outWght = malloc((nbHidNod * nbOut) * sizeof(double));

	double trainIn[nbTest][nbIn] = {{0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f}};
    double trainOut[nbTest][nbOut] = {{0.0f},{1.0f},{1.0f},{0.0f}};
	int order[4] = {0,1,2,3};

	for(int i = 0; i < nbIn; i++)
	{
		for(int j = 0; j < nbHidNod; j++)
		{
			hidWght[i * nbHidNod + j] = (double)rand()/(double)RAND_MAX; //getRandom(-10,10);
		}
	}

	for(int i = 0; i < nbHidNod; i++)
	{
		hidLayBias[i] = (double)rand()/(double)RAND_MAX;//getRandom(-10,10);
		for(int j = 0; j < nbOut; j++)
		{
			outWght[i * nbOut + j] = (double)rand()/(double)RAND_MAX;//getRandom(-10,10);

		}
	}

	for(int i = 0; i < nbOut; i++)
	{
		outLayBias[i] = (double)rand()/(double)RAND_MAX;//getRandom(-10,10);
	}

	//-----

	for(int step = 0; step < 10000; step++)
	{
		mix(order, nbTest);

		for(int t = 0; t<nbTest; t++)
		{
			int i = order[t];

			//START FORWARD PROPAGATION
			
			for(int j = 0; j < nbHidNod; j++)
			{
				double z = hidLayBias[j];
				for(int k = 0; k < nbIn; k++)
				{
					z +=  trainIn[i][k] * hidWght[k * nbHidNod + j];
				}
				hidLay[j] = sig(z);
			}

			for(int j = 0; j < nbOut; j++)
			{
				double z = outLayBias[j];
				for(int k = 0; k < nbHidNod; k++)
				{
					z += hidLay[k] * outWght[k*nbOut + j];
				}
				outLay[j] = sig(z);
			}

		    printf ("Input:%g %g Output:%g    Expected Output: %g\n",
                    trainIn[i][0], trainIn[i][1],
                    outLay[0], trainOut[i][0]);	

			//-----

			//BACKPROPAGATION

			double *deltaOut = malloc(nbOut * sizeof(double));
			for(int j =0; j < nbOut; j++)
			{
				double errorOut = (trainOut[i][j] - outLay[j]);
				deltaOut[j] = errorOut * Dsig(outLay[j]);
			}

			double *deltaHid = malloc(nbHidNod * sizeof(double));
			for(int j = 0; j<nbHidNod; j++)
			{
				double errorHid = 0.0f;
				for(int k = 0; k < nbOut; k++)
				{
					errorHid += deltaOut[k] * outWght[j * nbOut + k];
				}
				deltaHid[j] = errorHid * Dsig(hidLay[j]);
			}
			
			for(int j = 0; j < nbOut; j++)
			{
				outLayBias[j] += deltaOut[j] * pas;
				for(int k = 0; k<nbHidNod; k++)
				{
					outWght[k * nbOut + j] += hidLay[k] * deltaOut[j] * pas;
				}
			}

			for(int j = 0; j < nbHidNod; j++)
			{
				hidLayBias[j] += deltaHid[j] * pas;
				for(int k = 0; k<nbIn; k++)
				{
					hidWght[k * nbHidNod + j] += trainIn[i][k] * deltaHid[j] * pas;
				}
			}
		}
	}

	save(hidWght,1,4);
	save(hidLayBias,2,2);
	save(outWght,3,2);
	save(outLayBias,4,1);

	free(hidLay);
	free(hidLayBias);
	free(outLay);
	free(outLayBias);
	free(hidWght);
	free(outWght);
}
