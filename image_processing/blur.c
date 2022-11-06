#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"

#define W 540 //width of the image
#define H 480 // height of the image


/*Modifies a convultion kernel by mutiplying each values by k*/
void generate_kernel(double ker[3][3])
{
    int klen = 3;
    for (int i =0; i < klen; i++)
    {
        for(int j = 0; j<klen; j++)
        {
            ker[i][j] = 0.0625 * ker[i][j];
        }
    }
}

/*Creates a copy of the surface, runs the algo on the copy and applies it on the original */
void blur(Image image, double ker[3][3])
{
    generate_kernel(ker);
    Pixel** pixels = image.pixels;
    //int klen = sqrt(m);
    //int klen = 2;
    int w = image.w;
    int h = image.h;

    //Creating a copy of the initial surface
    Image temp = image_copy(&image);
    Pixel **tpix = temp.pixels;

    for(int i=1; i<h-1; i++)
    {
        for(int j=1; j<w-1; j++)
        {
            /*Applying kernel to each pixel of the image */
            unsigned int sum = 0;
            for(int k = -1; k<2; k++)
            {
                for(int l = -1; l<2; l++)
                {
                    sum+= tpix[i+k][j+l].r * ker[k+1][l+1];
                }
            }
            set_rgb(&pixels[i][j], sum, sum, sum);
        }
    }
    free_image(&temp);
}

