#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
    SDL_Surface* surface = load_image(argv[1]);
    draw(surface);
    return 0;
}
    //Image image = create_image(surface);
    
    //Converting image into grayscale
    //grayscale(image);
    
    //Applying Gaussian Blur
    //double **ker_gauss= {
      //  {1,2,1},
        //{2,4,2},
        //{1,2,1}};
    //blur(image, ker, 9, 0.0625);
    //SDL_Surface *processed = create_surface(image);
    //draw(processed);
