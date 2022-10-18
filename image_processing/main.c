#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "display.h"
#include "grayscale.h"
#include "blur.h"


// Event loop that calls the relevant event handler.
//
// renderer: Renderer to draw on.
// colored: Texture that contains the colored image.
// grayscale: Texture that contains the grayscale image.
void event_loop(SDL_Renderer* renderer, SDL_Texture* colored, SDL_Texture* grayscale)
{
    SDL_Event event;
    SDL_Texture* t = colored;
    draw(renderer, t);
    while (1)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
            {
                return;
                break;
            }
            case SDL_WINDOWEVENT_RESIZED:
            {
                draw(renderer, t);
                break;
            }
            case SDL_KEYDOWN:
            {
                if (t == colored)
                {
                    t = grayscale;
                }
                else
                {
                    t = colored;
                }
                draw(renderer, t);
                break;

            }
        }
    }
}


int main(int argc, char** argv)
{
    // Checks the number of arguments.
    if (argc != 2)
        errx(EXIT_FAILURE, "Usage: image-file");

    //Initializing and checking possible startup errors
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    SDL_Window* window= SDL_CreateWindow("Diplay", 0, 0, 640, 480, SDL_WINDOW_RESIZABLE);
    if(window == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

     //creating surface
   SDL_Surface* surface = load_image(argv[1]);

   //resizing
   int width = surface->w;
   int height = surface->h;
   SDL_SetWindowSize(window, width, height);
    
   //creating texture from image
   SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
   
   //processing grayscale
   surface_to_grayscale(surface);

   //Applying convolution with gaussian blur kernel
   apply_kernel(surface);

   //Creating texture from processed image
   SDL_Texture* grayscale =  SDL_CreateTextureFromSurface(renderer, surface);
   SDL_FreeSurface(surface);

   //calling the main loop
   event_loop(renderer, texture, grayscale);

   //Destroying objects
   SDL_DestroyRenderer(renderer);
   SDL_DestroyTexture(texture);
   SDL_DestroyTexture(grayscale);
   SDL_DestroyWindow(window);
   SDL_Quit();

    return EXIT_SUCCESS;
}
