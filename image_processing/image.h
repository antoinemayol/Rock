#ifndef IMAGE_H
#define IMAGE_H


/*********************STRUCTS**********************/
typedef struct Pixel Pixel;
typedef struct Image Image;

struct Pixel
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
};


struct Image
{
    Pixel **pixels;
    int w;
    int h;
};


/*********************METHODS**********************/

Image create_image(SDL_Surface* surface);
SDL_Surface* create_surface(Image image);
void get_rgb(Pixel pixel, unsigned int *r, unsigned int *g, unsigned *b);
void set_rgb(Pixel *pixel, unsigned int r, unsigned int g, unsigned int b);
Image image_copy(Image source);

#endif
