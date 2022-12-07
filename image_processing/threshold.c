#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <string.h>

#include "blur.h"
#include "image.h"

/*Applies Sobel algo to the image*/
void sobel(Image *image)
{
    //Generating convolution vertical(ker_gy) and horizontal(ker_gx) kernels
    double **ker_gx = malloc(sizeof(double*)*3);
    double **ker_gy = malloc(sizeof(double*)*3);
    for(int i = 0; i<3; i++)
    {
        ker_gx[i] = malloc(sizeof(double)*3);
        ker_gy[i] = malloc(sizeof(double)*3);
    }
    /*for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            if(i !=1)
            {
                ker_gx[i][j] = i-1;
                ker_gy[j][2-i] = i-1;
            }
            if(i == 1)
            {
                ker_gx[i][j] = -2+2*i;
                ker_gy[j][2-i] = -2+2*i;
            }
        }
    }*/

    //KerGY
    ker_gy[0][0]=1;
    ker_gy[0][1]=2;
    ker_gy[0][2]=1;
    ker_gy[1][0]=0;
    ker_gy[1][1]=0;
    ker_gy[1][2]=0;
    ker_gy[2][0]=-1;
    ker_gy[2][1]=-2;
    ker_gy[2][2]=-1;

    //KerGX
    ker_gx[0][0]=1;
    ker_gx[0][1]=0;
    ker_gx[0][2]=-1;
    ker_gx[1][0]=2;
    ker_gx[1][1]=0;
    ker_gx[1][2]=-2;
    ker_gx[2][0]=1;
    ker_gx[2][1]=0;
    ker_gx[2][2]=-1;
    Image gx = image_copy(image);
    Image gy = image_copy(image);

    convolution(&gx, ker_gx, 3);
    convolution(&gy, ker_gy, 3);
    for(int i =0; i<image->h; i++)
    {
        for(int j=0; j<image->w; j++)
        {
            unsigned int g = sqrt(pow(gx.pixels[i][j].r, 2)+pow(gy.pixels[i][j].r, 2));
            set_all(&image->pixels[i][j], g);
        }
    }
    free_image(&gx);
    free_image(&gy);
    for(int i = 0; i<3; i++)
    {
       free(ker_gx[i]);
       free(ker_gy[i]);
    }
    free(ker_gy);
    free(ker_gx);

}

/*Final process using gaussian convolution adaptive threshold */
void final_process(Image *image)
{
    int n = 3;
    double **ker = generate_kernel(n);
    //Pixel** pixels = image->pixels;
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

            //Applying threshold
            if(tpix[i][j].r < sum)
            {
                set_all(&image->pixels[i][j], 0);
            }
            else
            {
                set_all(&image->pixels[i][j], 255);
            }
        }
    }
    //freeing allocated memory of image copy
    free_image(&temp);
}


