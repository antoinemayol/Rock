#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "image.h"

/*Converts an RGB Pixel to grayscale*/
void pixel_to_grayscale(Pixel pixel)
{
    unsigned int r,g,b;
    get_rgb(pixel, &r, &g, &b);
    unsigned int average = 0.3*r + 0.59*g + 0.11*b;
    set_rgb(&pixel, average, average, average);
}

/* Applying grayscale to all pixels*/
void grayscale(Image *image)
{
    Pixel **pixels = image->pixels;
    for(int i =0; i<image->h; i++)
    {
        for(int j = 0; j<image->w; j++)
        {
            pixel_to_grayscale(pixels[i][j]);
        }
    }
}


/*
Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format)
{
    Uint8 r, g, b;
    SDL_GetRGB(pixel_color, format, &r, &g, &b);
    Uint32 average = 0.3*r + 0.59*g + 0.11*b;
    return SDL_MapRGB(format, average, average, average);
}

void surface_to_grayscale(SDL_Surface* surface)
{
    Uint32* pixels = surface->pixels;
    int len = surface->w * surface->h;
    SDL_PixelFormat* format = surface->format;
    SDL_LockSurface(surface);
    for (int i =0; i < len; i++)
    {
        pixels[i] = pixel_to_grayscale(pixels[i], format);  
    }
    SDL_UnlockSurface(surface);
}*/


