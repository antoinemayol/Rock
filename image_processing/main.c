#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "display.h"
#include "grayscale.h"
#include "blur.h"
#include "image.h"

int main(int argc, char** argv)
{
    // Checks the number of arguments.
    if (argc != 2)
    {
        errx(EXIT_FAILURE, "Usage: image-file");
    }
    SDL_Surface *surface = load_image(argv[1]);

    Image image = create_image(surface);
    grayscale(&image);
    //Applying Gaussian Blur
    double ker_gauss[3][3]= {
        {1.0,2.0,1.0},
        {2.0,4.0,2.0},
        {1.0,2.0,1.0}};
    blur(image, ker_gauss);
    SDL_Surface *processed = create_surface(&image);
    draw(processed);

    return 0;
}
