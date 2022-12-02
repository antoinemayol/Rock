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

int main(int argc, char** argv)
{
    // Checking the number of arguments.
    if (argc != 2)
    {
        errx(EXIT_FAILURE, "Usage: image-file");
    }

    //Loading image
    SDL_Surface *surface = load_image(argv[1]);

    //Converting SDL_Surface to struct Image
    Image image1 = create_image(surface);

    //Grayscale process
    Image image2 = image_copy(&image1);
    grayscale(&image2);

    //Increasing contrasts
    Image image3 = image_copy(&image2);
    increase_brightness(&image3);

    //Applying Gaussian Blur
    Image image4 = image_copy(&image3);
    gaussian_blur(&image4, 5);

    //Inversing colors
    /*Image image5 = image_copy(&image4);
      inverse(&image5);*/

    //Applying Sobel
    /*Image image4 = image_copy(&image3);
      sobel(&image4);*/
    //Final binarization process
    Image image5 = image_copy(&image4);
    otsu(&image5);

    SDL_Surface **surfaces = malloc(sizeof(SDL_Surface*)*5);
    surfaces[0] = create_surface(&image1);
    surfaces[1] = create_surface(&image2);
    surfaces[2] = create_surface(&image3);
    surfaces[3] = create_surface(&image4);
    surfaces[4] = create_surface(&image5);
    //surfaces[5] = create_surface(&image6);
    //surfaces[6] = create_surface(&image7);

    //Drawing step by steps final image
    draw(surfaces, 5);
    free_image(&image1);
    free_image(&image2);
    free_image(&image3);
    free_image(&image4);
    free_image(&image5);
    for(int i=0; i<5; i++)
    {
        SDL_FreeSurface(surfaces[i]);
    }
    free(surfaces);

    return 0;
}
    //NOTES:
    //Grayscale
    //Contrast
    //Brightness
    //Noise reducing
    //Gaussian Blur



