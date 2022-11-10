/*#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <string.h>

#include "otsu.h"
#include "blur.h"
#include "image.h"

*Step 1*
double* get_histo(Image *image)
{
    double *histo = initialize(256);
    for(int i = 0; i<image->h; i++)
    {
        for(int j = 0; j<image->w; j++)
        {
            histo[image->pixels[i][j].r]++;
        }
    }
    return histo;
}

double* initialize(int n)
{
    double *arr = malloc(sizeof(double) * n);
    for(int i = 0; i<n; i++)
    {
        arr[i] = 0;
    }
    return arr;
}

Step 5*
double get_sigma(int k, double ut, double *w, double *u)
{
    double a = (ut*w[k] - u[k]);
    double b = (w[k] * (1-w[k]));
    return (a*a)/b;
}

*Step 4
double get_omega(double *histo, int k)
{
    double res = 0;
    for(int i = 0; i <= k; i++)
    {
        res+= histo[i];
    
    return res;
}

*Step 3*
double get_mu(double *histo, int k)
{
    double res = 0;
    for(int i = 0; i<= k; i++)
    {
        res+= i * histo[i];
    }
    return res;
}

*Step 2*
void normalize(double *histo, int len)
{
    for(int i = 0; i < 256; i++)
    {
        histo[i] = histo[i] / len;
    }
}
*
//Applying otsu algorithm to get optimal threshold value/
unsigned int otsu(Image *image)
{
    double *histo = get_histo(image);
    normalize(histo, image->h * image->w);
    double *w = initialize(256);
    double *u = initialize(256);
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
    for(int i = 0; i<3; i++)
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
    }

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
}

*Final method to convert image from grayscale to binary
 * (Gaussian blur adaptive threshold)

void final_process(Image *image)
{
    int n = 24;
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





*
void final_process(Image *image, int s)
{
    //adaptive part
    int w = image->w;
    int h = image->h;
    double *arr = initialize(w * h);
    Image temp = image_copy(image);
    unsigned int sum = 0;

    for(int i=0; i<image->h; i++)
    {
        sum = 0;
        for(int j=0; j<image->w; j++)
        {
            sum+=temp.pixels[i][j].r;
            if(i==0)
            {
                arr[i * w + j] = sum;
            }
            else
            {
                arr[i*w + j] = sum + arr[(i-1)*w + j];
            }
        }
    }

    unsigned int threshold = otsu(image);
    for(int i = 0; i<image->h; i++)
    {
        for(int j = 0; j<image->w; j++)
        {
            int xa = i-s/2;
            int xb = i+s/2;
            int ya = j-s/2;
            int yb = j+s/2;
            int count = (xb-xa)*(yb-ya);
            
            //Checking border
            if(xa-1 >=0 && xb >=0 && ya-1 >=0 && yb>= 0
                    && xa < image->h && xb < image->h
                    && ya < image->w && yb < image->w)
            {
                sum = arr[xb*w+yb] - arr[xb*w+ya-1]
                    - arr[(xa-1)*w+yb] - arr[(xa-1)*w+ya-1];
            }
            
            //Basic threshold
            if(temp.pixels[i][j].r*count < (sum*(100-threshold)/100))
            {
                set_all(&image->pixels[i][j], 0);
            }
            else
            {
                set_all(&image->pixels[i][j], 255);
            }
        }
    }
    sobel(image);
}
*/
