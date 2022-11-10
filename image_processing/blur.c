#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "image.h"

/* Generates a Gaussian blur kernel of size n*n */
double** generate_kernel(int n)
{
    double sigma = 0.3*(n/2-1)+0.8;
    //double sigma = 0.5;
    //Allocating memory
    double **ker = calloc(n, sizeof(double *));
    for(int i = 0; i<n; i++)
    {
        ker[i] = calloc(n, sizeof(double));
    }
    double sum = 0;
    //Generating values using gaussian 2D filter algorithm
    int x=0;
    for(int i =-n/2; i <=n/2; i++)
    {
        int y = 0;
        for(int j =-n/2; j<=n/2; j++)
        {
            double tmp = exp(-(i*i+j*j)/(2*sigma*sigma))/(2*M_PI*sigma*sigma);
            ker[x][y] = tmp;
            sum+=tmp;
            y++;
        }
        x++;
    }
    for(int i = 0; i<n; i++)
    {
        for(int j =0; j<n; j++)
        {
            ker[i][j] = ker[i][j]/sum;
        }
    }
    return ker;
}
/*Switches 1 to 0 and 0 to 1*/
void inverse(Image *image)
{
    for(int i=0; i<image->h; i++)
    {
        for(int j=0; j<image->w; j++)
        {
            int inv = 255-image->pixels[i][j].r;
            set_all(&image->pixels[i][j], inv);
        }
    }
}

/*Creates a copy of the surface, runs the algo on the copy and applies it on the original */
void convolution(Image *image, double **ker, int n)
{
    Pixel** pixels = image->pixels;
    //int klen = sqrt(m);
    //int klen = 2;
    int w = image->w;
    int h = image->h;

    int c = n/2;
    //Creating a copy of the initial surface
    Image temp = image_copy(image);
    Pixel **tpix = temp.pixels;

    int x=0;
    int y=0;
    for(int i=c; i<h-c; i++)
    {
        for(int j=c; j<w-c; j++)
        {
            //Applying kernel to each pixel of the image
            unsigned int sum = 0;
            x=0;
            for(int k = -n+(n%2)+c; k<n-c; k++)
            {
                y=0;
                for(int l = -n+(n%2)+c; l<n-c; l++)
                {
                    sum+= tpix[i+k][j+l].r * ker[x][y];
                    y++;
                }
                x++;
            }
            set_rgb(&pixels[i][j], sum, sum, sum);
        }
    }
    //freeing allocated memory of image copy
    free_image(&temp);
}

void gaussian_blur(Image *image, int n)
{
    double** ker = generate_kernel(n);
    convolution(image, ker, n);
}

