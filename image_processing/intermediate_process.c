#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "image.h"

void bubble_sort(int *l, int len)
{
    int i, j, temp;
    for (i = 1; i < len; i++)
    {
        temp = l[i];
        for (j = i; j > 0 && l[j-1]>temp; j--)
        {
            l[j] = l[j-1];
        }
        l[j] = temp;
    }
}

/*Increases the contrast of the image using a specific factor*/
void noise_reduction(Image *image)
{
    int n = 3;
    int c = n/2;
    int h = image->h;
    int w = image->w;

    for(int i=c; i<h-c; i++)
    {
        for(int j=c; j<w-c; j++)
        {
            //Applying noise reduction algorithm for each pixel
            int x=0;
            int count = 0;
            int *arr = malloc(sizeof(int)*9);
            for(int k = -n+(n%2)+c; k<n-c; k++)
            {
                int y=0;
                for(int l = -n+(n%2)+c; l<n-c; l++)
                {
                    arr[count] = image->pixels[i][j].r;
                    y++;
                    count++;
                }
                x++;
            }
            bubble_sort(arr, 9);
            set_all(&image->pixels[i][j], arr[4]);
            free(arr);
        }
    }
}

void increase_contrast(Image *image, int f)
{
    for(int i = 0; i < image->h; i++)
    {
        for(int j = 0; j < image->w; j++)
        {
            for(int k = 0; k < f; k++)
            {
                unsigned int x = image->pixels[i][j].r;
                unsigned int min = k*(255/f);
                unsigned int max = (k+1)*(255/f);
                if(x >= min && x <= max)
                {
                    set_all(&image->pixels[i][j], max);
                }
            }
        }
    }
}

/*Returns the highest color among all pixels*/
unsigned int get_max_color(Image *image)
{
    unsigned int max = 0;
    for(int i = 0; i < image->h; i++)
    {
        for(int j = 0; j < image->w; j++)
        {
            if(image->pixels[i][j].r > max)
            {
                max = image->pixels[i][j].r;
            }
        }
    }
    return max;
}

/*Increases default brightness of the image*/
void increase_brightness(Image *image)
{
    unsigned int max = get_max_color(image);
    for(int i = 0; i < image->h; i++)
    {
        for(int j = 0; j < image->w; j++)
        {
            unsigned int p = image->pixels[i][j].r;
            if(p > max)
            {
                max = p;
            }
            set_all(&image->pixels[i][j], 255 - p * (255/max));
        }
    }
}
