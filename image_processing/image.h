#ifndef IMAGE_H
#define IMAGE_H


/*********************STRUCTS**********************/

 typedef struct Pixel
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
} Pixel;


typedef struct Image
{
    Pixel **pixels;
    int w;
    int h;
} Image;


/*********************METHODS**********************/
void free_image(Image *image);
Image create_image(SDL_Surface* surface);
SDL_Surface* create_surface(Image *image);
void get_rgb(Pixel pixel, unsigned int *r, unsigned int *g, unsigned *b);
void set_rgb(Pixel *pixel, unsigned int r, unsigned int g, unsigned int b);
Image image_copy(Image *source);
void set_all(Pixel *pixel, unsigned int k);
int* export_array(Image *image);
void resize_image(Image *image, int nw, int nh);

#endif
