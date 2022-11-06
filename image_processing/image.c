#include <stdlib.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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


/***********************************************/
/********************IMAGE**********************/
/***********************************************/


/*Creates an Image from the built surface*/
Image create_image(SDL_Surface* surface)
{
    //Initializing parameters
    Pixel **pixels = NULL;
    int w = surface->w;
    int h = surface->h;
    SDL_PixelFormat* format = surface->format;
    SDL_Color color;
    //Calling constructor/creating image
    Image image;
    image.pixels = pixels;
    image.w = w;
    image.h = h;

    //Allocatiing memory for pixels array(simple then double dimension)
    image.pixels = (Pixel **)calloc(h, sizeof(Pixel *));
    for (int p; p < h; p++)
    {
        image.pixels[p] = (Pixel *)calloc(w, sizeof(Pixel));
    }
    
    //filling image pixels one by one from surface pixels
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            Uint32 pix = get_pixel(surface, i, j);
            SDL_GetRGB(pix, format, &color.r, &color.g, &color.b);
            image.pixels[i][j].r = color.r; 
            image.pixels[i][j].g = color.g; 
            image.pixels[i][j].b = color.b; 
        }
    }
    return image;
}

SDL_Surface* create_surface(Image image)
{
    //Initializing new surface
    SDL_Surface *surface = SDL_CreateRGBSurface(0, image.w, image.h, 32, 0 , 0, 0, 0);
    int h = image.h;
    int w = image.w;
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            //Getting pixel from image and setting new pixel to surface
            Pixel pix = image.pixels[i][j];
            Uint32 pixel= SDL_MapRGB(surface->format, pix.r, pix.g, pix.b);
            set_pixel(surface, pixel, i, j);
        }
    }
    return surface;
}

void get_rgb(Pixel pixel, unsigned int *r, unsigned int *g, unsigned *b)
{
    *r = pixel.r;
    *g = pixel.g;
    *b = pixel.b;
}

void set_rgb(Pixel *pixel, unsigned int r, unsigned int g, unsigned int b)
{
    pixel->r = r;
    pixel->g = g;
    pixel->b = b;
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
Image image_copy(Image source)
{
    //Initializing new image
    Image dest;
    dest.pixels = NULL;
    int w = source.w;
    int h = source.h;
    dest.w = w;
    dest.h = h;
    
    //Allocating memory for new pixels array
    dest.pixels = (Pixel **)calloc(h, sizeof(Pixel *));
    for (int p; p < h; p++)
    {
        dest.pixels[p] = (Pixel *)calloc(w, sizeof(Pixel)); 
    }

    //Copying pixels one by one from source to destination
    for(int i = 0; i<h; i++)
    {
        for(int j = 0; j<w; j++)
        {
            dest.pixels[i][j] = source.pixels[i][j];
        }
    }
    free_image(&dest);
    return dest;
}
