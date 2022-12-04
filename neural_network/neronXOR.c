#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <err.h>
#include <time.h>
#include <dirent.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "save_and_load.h"
#include "../image_processing/processing_final.h"
//#include "data_struc.h"

/* generate a random floating point number from min to max */
double randfrom(double min, double max)
{

    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

//Sigmoid function
double sig(double z)
{
	return 1 / (1 + exp(-z));
}

//Derivate of sigmoid function
double Dsig(double z)
{
	return z * (1 - z);
}

//Randomly mix an array
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

#define nbIn 625
#define nbHidLay 1
#define nbHidNod 122
#define nbOut 10
/*
double testMat6[225] =   	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
							 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,
							 0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
							 0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,
							 0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,
							 0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
							 0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
							 0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
							 0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,
							 0,0,1,1,1,0,0,1,1,0,0,0,0,0,0,
							 0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,
							 0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,
							 0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,
							 0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
							 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

double testMat3[225] =   	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
							 0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
							 0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
							 0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,
							 0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
							 0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
							 0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,
							 0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
							 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
							 0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
							 0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
							 0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,
							 0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
							 0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
							 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
*/

//The network look like this :
// Input 1 -- O -- O
// 	           \ /  \
//              X    O -- Output
//             / \  /
// Input 2 -- O -- O 

//Créer fonctions qui créer le réseau et l'init

#define nbTest 1

double** get_trainset(char* num )
{
    double** res = malloc(6 * sizeof(625 * sizeof(double)));

    struct dirent **namelist;
   	int n;
	int i = 0;

    char* dir = strcat("dataset/",num);

   	n = scandir(dir, &namelist, NULL, alphasort);
   	if (n < 0)
       	perror("scandir");
   	else
	{
       	while (i<n)
		{
            char* fi = strcat(dir,namelist[i]->d_name);
            double* tmp = train_convert(fi);

            res[i] = tmp;
            i++;
       	}
       	free(namelist);
   	}
	return res;


}

//Proceeding the creation and the application of neural network for XOR
void proceed(int limit)
{
	//Setting learning rate
	double pas = 0.1f;

	//Arrays of neurons
	//double *hidLay = load("neurones/nerons2.txt");
    double *hidLay = malloc(nbHidNod * sizeof(double));
	//double *outLay = load("neurones/nerons5.txt");
    double *outLay = malloc(nbOut * sizeof(double));

	//Arrays of neurons bias
	//double *hidLayBias = load("neurones/nerons3.txt");
    double *hidLayBias = malloc(nbHidNod * sizeof(double));
	//double *outLayBias = load("neurones/nerons6.txt");
    double *outLayBias = malloc(nbOut * sizeof(double));

	//Arrays of Weight
	//double *hidWght = load("neurones/nerons1.txt");
    double *hidWght = malloc((nbIn * nbHidNod) * sizeof(double));
	//double *outWght = load("neurones/nerons4.txt");
    double *outWght = malloc((nbHidNod * nbOut) * sizeof(double));

	//Inputs and expected outputs
	double trainIn[nbTest][nbIn] = {};

    double trainOut[nbTest][nbOut] = {{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f}};
								//      0	  1     2   3    4    5    6    7    8    9
	int order[1] = {0};

	//Initialize layers with random value close to 0
	for(int i = 0; i < nbIn; i++)
	{
		for(int j = 0; j < nbHidNod; j++)
		{
			hidWght[i * nbHidNod + j] = randfrom(-0.5,0.5);//(double)rand()/(double)RAND_MAX;
		}
	}

	for(int i = 0; i < nbHidNod; i++)
	{
		hidLayBias[i] = randfrom(-0.5,0.5);//(double)rand()/(double)RAND_MAX;
		for(int j = 0; j < nbOut; j++)
		{
			outWght[i * nbOut + j] = randfrom(-0.5,0.5);//(double)rand()/(double)RAND_MAX;

		}
	}

	for(int i = 0; i < nbOut; i++)
	{
		outLayBias[i] = randfrom(-0.5,0.5);//(double)rand()/(double)RAND_MAX;
	}

	//-----
	for(int step = 0; step < limit; step++)
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
				//printf("Z = %f\n",z);
				outLay[j] = sig(z);
				//printf("outl = %f\n",outLay[j]);
			}

			//Printing results as they come
			if(limit-step <= 1)
			{
		    	printf ("Input : %d \nOutputs :\n 0 : %f\n 1: %f\n 2: %f\n 3: %f\n 4: %f\n 5: %f\n 6: %f\n 7: %f\n 8: %f\n 9: %f\n Expected Output: %g\n\n",
                    	i, outLay[0], outLay[1], outLay[2], outLay[3], outLay[4], outLay[5], outLay[6], outLay[7], outLay[8], outLay[9],
						trainOut[i][0]);
			}
			//-----

			//BACKPROPAGATION

			//Compute difference between result and expected
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

			//Update weights between nodes
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
	//Save neurons, weights and biases in "neurones/" folder
	//and release memory
	save(hidWght,1,nbIn*nbHidNod);
	free(hidWght);
	save(hidLay,2,nbHidNod);
	free(hidLay);
	save(hidLayBias,3,nbHidNod);
	free(hidLayBias);
	save(outWght,4,nbOut*nbHidNod);
	free(outWght);
	save(outLay,5,nbOut);
	free(outLay);
	save(outLayBias,6,nbOut);
	free(outLayBias);
}

void forward(double* input)
{
    double* hidwgt = load("neurones/nerons1.txt");
    double* hidlay = load("neurones/nerons2.txt");
    double* hidlayBias = load("neurones/nerons3.txt");

    double* outwgt = load("neurones/nerons4.txt");
    double* outlay = load("neurones/nerons5.txt");
    double* outlayBias = load("neurones/nerons6.txt");

    for(int j = 0; j < nbHidNod; j++)
    {
        double z = hidlayBias[j];
        for(int k = 0; k < nbIn; k++)
        {
            z +=  input[k] * hidwgt[k * nbHidNod + j];
            //printf("little zhid  = %f\n",z);
        }
        //printf("Zhid = %f\n",z);
        hidlay[j] = sig(z);
        //printf("hidl = %f\n",hidlay[j]);
    }

    for(int j = 0; j < nbOut; j++)
    {
        double z = outlayBias[j];
        for(int k = 0; k < nbHidNod; k++)
        {
            z += hidlay[k] * outwgt[k*nbOut + j];
        }
        //printf("Zout = %f\n",z);
        outlay[j] = sig(z);
        //printf("outl = %f\n",outlay[j]);
    }

    for(int i = 0; i < nbOut; i++)
    {
        printf("number %d : %f \n",i+1,outlay[i]);
    }
}

int main(int argc, char **argv)
{
    /*
	if(strcmp("--train",argv[1]) == 0 && argc == 3)
    {
        int limit = atoi(argv[2]);
        printf("SETTED LIMIT : %d\n\n",limit);

        if(limit < 0 || limit > 50000)
        {
            errx(1,"limit is too high !\n");
        }

        proceed(limit);
        return 0;
    }

    if(strcmp(argv[1], "--exec") == 0 && argc == 2)
    {
        forward(testMat1);
        return 0;
    }
    errx(1,"Call with --train {arg} or --exec");
    */

}
