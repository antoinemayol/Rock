#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <string.h>

#include "otsu.h"
#include "blur.h"
#include "image.h"

//Step 1
float* get_histo(Image *image)
{
    float *histo = initialize(256);
    for(int i = 0; i<image->h; i++)
    {
        for(int j = 0; j<image->w; j++)
        {
            histo[image->pixels[i][j].r]++;
        }
    }
    int N = image->w*image->h;
    for(int i =0; i<256; i++)
    {
        histo[i]=histo[i]/N;
    }
    return histo;
}

float* initialize(int n)
{
    float *arr = malloc(sizeof(double) * n);
    for(int i = 0; i<n; i++)
    {
        arr[i] = 0;
    }
    return arr;
}

//Step 5
float get_sigma(double ut, float w, float u)
{
    float a = (ut*w[k] - u[k]);
    float b = (w[k] * (1-w[k]));
    return (a*a)/b;
}

//Step 4
int get_omega(double *histo, int k)
{
    float res = 0;
    for(int i = 0; i <= k; i++)
        res+= histo[i];

    return res;
}

//Step 3
float get_mu(double *histo, int k)
{
    float res = 0;
    for(int i = 0; i< k; i++)
    {
        res+= i * histo[i];
    }
    return res;
}

//Step 2
void normalize(double *histo, int len)
{
    for(int i = 0; i < 256; i++)
    {
        histo[i] = histo[i] / len;
    }
}

//Applying otsu algorithm to get optimal threshold value/
void otsu(Image *image)
{
    float *histo = get_histo(image);
    normalize(histo, image->h * image->w);
    float *w = initialize(256);
    float *u = initialize(256);
    float max = -1;
    float res;

    for(int i = 0; i<256; i++)
    {
        w[i] = get_omega(histo, i);
        u[i] = get_mu(histo, i);
    }
    double ut = get_mu(histo, 256);

    for(int k=0; k<256; k++)
    {
        int tmp = get_sigma(ut, w[k], u[k]);
        if(tmp > max)
        {
            max = tmp;
            res = k;
        }
    }
    int threshold = (int)res;

    //Threshold
    for(int i = 0; i<image->h; i++)
    {
        for(int j = 0; j < image->w; j++)
        {
            if(image->pixels[i][j].r < res)
            {
                set_all(&image->pixels[i][j], 0);
            }
            else
            {
                set_all(&image->pixels[i][j], 255);
            }
        }
    }

    free(histo);
    free(w);
    free(u);
}
