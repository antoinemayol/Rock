#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "display.h"
#include "grayscale.h"
#include "blur.h"
#include "image.h"
#include "threshold.h"
#include "otsu.h"
#include "processing_final.h"
#include "intermediate_process.h"

int* image_processing(char* path, int *w, int *h)
{
    //Loading image
    SDL_Surface *surface = load_image(path);

    //Converting SDL_Surface to struct Image
    Image image = create_image(surface);

    *w = image.w;
    *h = image.h;

    //Grayscale process
    grayscale(&image);

    //Increasing Brightness and inversing colors
    increase_brightness(&image);

    //Bluring image
    gaussian_blur(&image,5);

    //Final binarization process
    otsu(&image);

    //Converting pixels array to int array
    int *res = pixels_to_int(&image);

    return res;
}
