#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "image.h"

/*Increases the contrast of the image using a specific factor*/
void increase_contrast(Image *image, int f)
{
    for(int i = 0; i < image->h; i++)
    {
        for(int j = 0; j < image->w; j++)
        {
            for(int k = 0; k < f; k++)
            {
                unsigned int min = k*(255/f);
                unsigned int max = (k+1)*(255/f);
                if(image->pixels[i][j].r >= min
                        && image->pixels[i][j].r <= max)
                {
                    set_all(&image->pixels[i][j], max);
                }
            }
        }
    }
}

/*Increases default brightness of the image*/
void increase_brightness(Image *image)
{
    unsigned int max = 0;
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
