#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <string.h>

#include "image.h"

#define W 540 //width of the image
#define H 480 // height of the image


/*Modifies a convultion kernel by mutiplying each values by k*/
void generate_kernel(double **ker, double k)
{
    int klen = 3;
    for (int i =0; i < klen; i++)
    {
        for(int j = 0; j<klen; j++)
        {
            ker[i][j] = k * ker[i][j];
        }
    }
}

/*Creates a copy of the surface, runs the algo on the copy and applies it on the original */
void blur(Image image, double **ker, float x)
{ 
    generate_kernel(ker,x);
    Pixel** pixels = image.pixels;
    //int klen = sqrt(m);
    int klen = 3;
    int w = image.w;
    int h = image.h;

    //Creating a copy of the initial surface
    Image temp = image_copy(image);
    Pixel **tpix = temp.pixels;
    
    for(int i=klen; i<h; i++)
    {
        for(int j=klen; j<w; j++)
        {
            /*Applying kernel to each pixel of the image */
            unsigned int sum = 0;
            for(int k = -klen; k<klen-1; k++)
            {
                for(int l = -klen; l<klen; l++)
                {
                    sum+= tpix[i+k][j+l].r * ker[i+k][j+l]; 
                }
            }
            set_rgb(&pixels[i][j], sum, sum, sum);
        }
    }
    /*
    for (int z = 3; z < len-3; z++)
    {
        Uint8 acc = 0;
        int n = 0;
        Uint8 r,g,b;
        get_rgb(tpix[z], format, &r, &g, &b);

        for(int k = -klen; k < klen; k++)
        {
            for(int l = -klen; l < klen; l++)
            {
                int i = z / W;
                int j = z % W;
                SDL_GetRGB(tpix[(z+k) * W + (z+l)], format, &r, &g, &b);
                acc += ker[n] * r;
                n++;
                //if((i+k) >= 0 && (i+k) < H && (i+l) >= 0 && (j+l) < W)
                //{
                   // SDL_GetRGB(tpix[(i+k) * W + (j+l)], format, &r, &g, &b);
                    //acc += ker[n] * r;
                    //n++;
                //}
            }
        }
        pixels[z] = SDL_MapRGB(format, acc, acc, acc);
    } */
}

