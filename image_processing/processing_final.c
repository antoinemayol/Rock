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

int* image_processing(char* path)
{
    //Loading image
    SDL_Surface *surface = load_image(path);

    //Converting SDL_Surface to struct Image
    Image image = create_image(surface);
    //Grayscale process
    grayscale(&image);

    //Bluring image
    gaussian_blur(&image, 5);

    //Final binarization process
    final_process(&image);
    sobel(&image);
    return 0;
}
