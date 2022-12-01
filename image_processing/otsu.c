#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <string.h>

#include "otsu.h"
#include "blur.h"
#include "image.h"

//Step 1
double* get_histo(Image *image)
{
    double *histo = initialize(256);
    for(int i = 0; i<image->h; i++)
    {
        for(int j = 0; j<image->w; j++)
        {
            histo[(int)image->pixels[i][j].r]++;
        }
    }
    int N = image->w*image->h;
    for(int i =0; i<256; i++)
    {
        histo[i]=histo[i]/N;
    }
    return histo;
}

double* initialize(int n)
{
    double *arr = malloc(sizeof(double) * n);
    for(int i = 0; i<n; i++)
    {
        arr[i] = 0;
    }
    return arr;
}

//Step 5
double get_sigma(int k, double ut, double *w, double *u)
{
    double a = (ut*w[k] - u[k]);
    double b = (w[k] * (1-w[k]));
    return (a*a)/b;
}

//Step 4
double get_omega(double *histo, int k)
{
    double res = 0;
    for(int i = 0; i <= k; i++)
        res+= histo[i];

    return res;
}

//Step 3
double get_mu(double *histo, int k)
{
    double res = 0;
    for(int i = 0; i< k; i++)
    {
        res+= (double)i * histo[i];
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
    double *histo = get_histo(image);
    normalize(histo, image->h * image->w);
    double *w = initialize(256);
    double *u = initialize(256);
    double max = -1;
    double res;

    for(int i = 0; i<256; i++)
    {
        w[i] = get_omega(histo, i);
        u[i] = get_mu(histo, i);
    }
    double ut = get_mu(histo, 256);

    for(int k=0; k<256; k++)
    {
        double tmp = get_sigma(k , ut, w, u);
        if (tmp > max)
        {
            max = tmp;
            res = k;
        }
    }

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
