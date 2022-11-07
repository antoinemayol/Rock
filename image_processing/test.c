#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "display.h"
#include "grayscale.h"
#include "blur.h"
#include "image.h"
#include "otsu.h"

int* test(void)
{
    SDL_Surface *surface = load_image("images/image_01.jpeg");

    Image image = create_image(surface);
    grayscale(&image);
    //Applying Gaussian Blur
    double ker_gauss[3][3]= {
        {1.0,2.0,1.0},
        {2.0,4.0,2.0},
        {1.0,2.0,1.0}};
    blur(&image, ker_gauss);
    inverse(&image);
    //TODO: Reogarnise directories
    //TODO: Sobel(detecrtion de contours)
    final_process(&image);
    int* matrix = export_array(&image);
    return matrix;
}
