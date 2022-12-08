#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../image_processing/processing_final.h"
#include "../image_processing/image.h"
#include "../image_processing/display.h"
#include "LineParameter.h"

void draw_lines(struct LineParameter *lp, char* path)
{
    //Creating Image
    SDL_Surface *surface = load_image(path);

    //Converting SDL_Surface to struct Image
    Image image = create_image(surface);
    float rho = lp->distance;
    float teta = lp->angle;
    for(int i = 0; i < image.h; i++)
    {
        //Line equation from angle and distance
        int j = (rho*i*cos(teta))/sin(teta);
        image.pixels[i][j].r = 0;
        image.pixels[i][j].b = 255;
        image.pixels[i][j].g = 0;
    }
    draw_image(&image);
}
