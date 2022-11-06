#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include "image.h"

/*Converts an RGB Pixel to grayscale*/
void pixel_to_grayscale(Pixel *pixel)
{
    unsigned int r,g,b;
    get_rgb(*pixel, &r, &g, &b);
    unsigned int average = 0.3*r + 0.59*g + 0.11*b;
    set_rgb(pixel, average, average, average);
}

/* Applying grayscale to all pixels*/
void grayscale(Image *image)
{
    Pixel **pixels = image->pixels;
    for(int i =0; i<image->h; i++)
    {
        for(int j = 0; j<image->w; j++)
        {
            pixel_to_grayscale(&pixels[i][j]);
        }
    }
}

