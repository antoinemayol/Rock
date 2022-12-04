#include <stdlib.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "image.h"


/*****************************************************/
/**********************CONVERTER**********************/
/*****************************************************/


/*Converts a Surface pixel to a Pixel*/
Uint32 get_pixel(SDL_Surface *surface, int x, int y)
{
    int b = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + x * surface->pitch + y * b;

    switch (b)
    {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;
    }
}

/*Converts a Pixel to a Surface pixel*/
void set_pixel(SDL_Surface *surface,Uint32 pixel, unsigned x, unsigned y)
{
    int b = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + x * surface->pitch + y * b;

    switch (surface->format->BytesPerPixel)
    {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        }
        else
        {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

/*Converts a Pixel array to int array of bytes*/
int* pixels_to_int(Image *image)
{
    //Getting width and height from image
    int w = image->w;
    int h = image->h;

    //Allocating memory for pixels array(simple then double dimension)
    int *res = malloc(h*w*sizeof(int));

    for (int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            if(image->pixels[i][j].r == 0)
            {
                res[i*w+j] = 0;
            }
            else
            {
                res[i*w+j] = 1;
            }
        }
    }
    return res;
}

/*Converts a Pixel array to double array of bytes*/
double* pixels_to_double(Image *image)
{
    //Getting width and height from image
    int w = image->w;
    int h = image->h;

    //Allocating memory for pixels array(simple then double dimension)
    double *res = malloc(h*w*sizeof(double));

    for (int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            if(image->pixels[i][j].r == 0)
            {
                res[i*w+j] = 0;
            }
            else
            {
                res[i*w+j] = 1;
            }
        }
    }
    return res;
}


/***********************************************/
/********************IMAGE**********************/
/***********************************************/
/*Creates an empty image of size(w)x(h) filled with white pixels*/

Image create_empty_image(int w, int h)
{
    //Calling constructor/creating image
    Image image = { .pixels = NULL, .w = w, .h = h};

    //Allocatiing memory for pixels array(simple then double dimension)
    image.pixels = (Pixel **)calloc(h, sizeof(Pixel *));
    for (int p = 0; p < h; p++)
    {
        image.pixels[p] = (Pixel *)calloc(w, sizeof(Pixel));
        if (image.pixels[p] == NULL)
        {
            errx(EXIT_FAILURE, "Memory allocation error");
        }
    }

    //filling image pixels one by one from surface pixels
    for( int i = 0;i < h; i++)
    {
        for(int j = 0;j < w; j++)
        {
            image.pixels[i][j].r = 0;
            image.pixels[i][j].g = 0;
            image.pixels[i][j].b = 0;
        }
    }
    return image;
}


/*Creates an Image from the built surface*/
Image create_image(SDL_Surface *surface)
{
    //Initializing parameters
    int w = surface->w;
    int h = surface->h;
    SDL_Color color;
    //Calling constructor/creating image
    Image image = { .pixels = NULL, .w = w, .h = h};

    //Allocatiing memory for pixels array(simple then double dimension)
    image.pixels = (Pixel **)calloc(h, sizeof(Pixel *));
    for (int p = 0; p < h; p++)
    {
        image.pixels[p] = (Pixel *)calloc(w, sizeof(Pixel));
        if (image.pixels[p] == NULL)
        {
            errx(EXIT_FAILURE, "Memory allocation error");
        }
    }

    //filling image pixels one by one from surface pixels
    for( int i = 0;
 i < h; i++)
    {
        for(int j = 0;
j < w; j++)
        {
            Uint32 pix = get_pixel(surface, i, j);
            SDL_GetRGB(pix, surface->format, &color.r, &color.g, &color.b);
            image.pixels[i][j].r = color.r;
            image.pixels[i][j].g = color.g;
            image.pixels[i][j].b = color.b;
        }
    }

    return image;
}

/*Creates an SDL Surface from an Image*/
SDL_Surface* create_surface(Image *image)
{
    //Initializing new surface
    SDL_Surface *surface = SDL_CreateRGBSurface(0, image->w, image->h, 32, 0 , 0, 0, 0);
    int h = image->h;
    int w = image->w;
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            //Getting pixel from image and setting new pixel to surface
            Pixel pix = image->pixels[i][j];
            Uint32 pixel= SDL_MapRGB(surface->format, pix.r, pix.g, pix.b);
            set_pixel(surface, pixel, i, j);
        }
    }
    return surface;
}

/*Bilinear algorithm applied to the Image in order to resize it to (nw)x(nh)*/
void resize_image(Image *image, int nw, int nh)
{
    //Deep copy of image
    Image res = create_empty_image(nw,nh);

    //Old image dimensions
    int iw = image->w;
    int ih = image->h;

    //Initializing ratios
    float xr = (float)(iw-1)/(nw-1);
    float yr = (float)(ih-1)/(nh-1);

    for(int i=0; i<nh; i++)
    {
        for(int j=0; j<nw; j++)
        {
            //Calculating ratio/index coords
            unsigned int xl = floor(xr*j);
            unsigned int xh = ceil(xr*j);
            unsigned int yl = floor(yr*i);
            unsigned int yh = ceil(yr*i);

            //Calculating weight values
            unsigned int xw = (xr*j)-xl;
            unsigned int yw = (yr*i)-yl;

            //Calculation coefficients
            unsigned int a = image->pixels[yl][xl].r;
            unsigned int b = image->pixels[yl][xh].r;
            unsigned int c = image->pixels[yh][xl].r;
            unsigned int d = image->pixels[yh][xh].r;

            //Processing final value for pixel
            unsigned int val= a * (1-xw) * (1-yw)
                + b * xw * (1-yw)
                + c * yw * (1-xw)
                + d * xw * yw;

            //Applying final value to pixel
            set_all(&res.pixels[i][j], val);
        }
    }
    *image=res;
    //Assiging new parameters to image
    /*image->pixels = res.pixels;
    image->w = res.w;
    image->h = res.h;*/
}

/* Gets r g and values of a pixel*/
void get_rgb(Pixel pixel, unsigned int *r, unsigned int *g, unsigned *b)
{
    *r = pixel.r;
    *g = pixel.g;
    *b = pixel.b;
}

/*Set r b and b values for each pixels*/
void set_rgb(Pixel *pixel, unsigned int r, unsigned int g, unsigned int b)
{
    pixel->r = r;
    pixel->g = g;
    pixel->b = b;
}

/*Sets all pixels values to k*/
void set_all(Pixel *pixel, unsigned int k)
{
    pixel->r = k;
    pixel->g = k;
    pixel->b = k;

}

/*Extracts the pixels array to a binary matrix*/
int* export_array(Image *image)
{
    int *arr = malloc(sizeof(int)*image->w*image->h);
    for(int i = 0; i<image->h; i++)
    {
        for(int j = 0; j<image->w; j++)
        {
            arr[i*image->w+j] = ((int)image->pixels[i][j].r == 255);
        }
    }
    return arr;
}

/*Frees memory from created image addressed size*/
void free_image(Image *image)
{
    for(int p = 0; p< image->h; p++)
    {
        free(image->pixels[p]);
    }
    free(image->pixels);
}

/*Deep copies an image*/
Image image_copy(Image *source)
{
    //Initializing new image
    Image dest;
    dest.pixels = NULL;
    int w = source->w;
    int h = source->h;
    dest.w = w;
    dest.h = h;

    //Allocating memory for new pixels array
    dest.pixels = (Pixel **)calloc(h, sizeof(Pixel *));
    for (int p = 0; p < h; p++)
    {
        dest.pixels[p] = (Pixel *)calloc(w, sizeof(Pixel));
    }

    //Copying pixels one by one from source to destination
    for(int i = 0; i<h; i++)
    {
        for(int j = 0; j<w; j++)
        {
            dest.pixels[i][j] = source->pixels[i][j];
        }
    }
    return dest;
}
