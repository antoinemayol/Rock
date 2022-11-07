#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"

double* initialize();
/*Step 1*/
double* get_histo(Image *image)
{
    double *histo = initialize();
    for(int i = 0; i<image->h; i++)
    {
        for(int j = 0; j<image->w; j++)
        {
            histo[image->pixels[i][j].r]++;
        }
    }
    return histo;
}

double* initialize()
{
    double *arr = malloc(sizeof(double) * 256);
    for(int i = 0; i<256; i++)
    {
        arr[i] = 0;
    }
    return arr;
}

/*Step 5*/
double get_sigma(int k, double ut, double *w, double *u)
{
    double a = (ut*w[k] - u[k]);
    double b = (w[k] * (1-w[k]));
    return (a*a)/b;
}

/*Step 4*/
double get_omega(double *histo, int k)
{
    double res = 0;
    for(int i = 0; i <= k; i++)
    {
        res+= histo[i];
    }
    return res;
}

/*Step 3*/
double get_mu(double *histo, int k)
{
    double res = 0;
    for(int i = 0; i<= k; i++)
    {
        res+= i * histo[i];
    }
    return res;
}

/*Step 2*/
void normalize(double *histo, int len)
{
    for(int i = 0; i < 256; i++)
    {
        histo[i] = histo[i] / len;
    }
}

/*Applying otsu algorithm to get optimal threshold value*/
unsigned int otsu(Image *image)
{
    double *histo = get_histo(image);
    normalize(histo, image->h * image->w);
    double *w = initialize();
    double *u = initialize();
    double max = 0;
    int res;

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
    free(histo);
    free(w);
    free(u);
    return res;
}

/*Final method to convert image from grayscale to binary 
 * (Otsu + Threshold)*/
void final_process(Image *image)
{
    unsigned int threshold = otsu(image);
    for(int i = 0; i<image->h; i++)
    {
        for(int j = 0; j<image->w; j++)
        {
            if(image->pixels[i][j].r < threshold)
            {
                set_all(&image->pixels[i][j], 0);
            }
            else
            {
                set_all(&image->pixels[i][j], 255);
            }
        }
    }
}
