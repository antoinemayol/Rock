#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <string.h>

#include "otsu.h"
#include "blur.h"
#include "image.h"


float* initialize(int n)
{
    float *arr = malloc(sizeof(float) * n);
    for(int i = 0; i<n; i++)
    {
        arr[i] = 0;
    }
    return arr;
}


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
    return histo;
}

//Step 5
float get_sigma(float ut, float wk, float uk)
{
    float a = (ut*wk - uk);
    float b = (wk * (1-wk));
    return pow(a,2)/b;
}

//Step 4
float get_omega(float *histo, int k)
{
    float res = 0;
    for(int i = 0; i < k; i++)
        res+= histo[i];

    return res;
}

//Step 3
float get_mu(float *histo, int k)
{
    float res = 0;
    for(int i = 0; i< k; i++)
    {
        res+= i * histo[i];
    }
    return res;
}

//Step 2
void normalize(float *histo, int len)
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
    float res = 0;

    for(int i = 0; i<256; i++)
    {
        w[i] = get_omega(histo, i);
        u[i] = get_mu(histo, i);
    }
    float ut = get_mu(histo, 256);

    for(int k=0; k<256; k++)
    {
        float tmp = get_sigma(ut, w[k], u[k]);
        if(tmp > max)
        {
            max = tmp;
            res = k;
        }
    }
    unsigned int threshold = (unsigned int)res;
    //Threshold
    for(int i = 0; i<image->h; i++)
    {
        for(int j = 0; j < image->w; j++)
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

    free(histo);
    free(w);
    free(u);
}
