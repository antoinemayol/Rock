#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "rotation.h"

//initialisation taille du display
//
const int INIT_WIDTH = 640;
const int INIT_HEIGHT = 400;

void draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer,texture,NULL,NULL);
    SDL_RenderPresent(renderer);
}

void event_loop(SDL_Renderer* renderer, SDL_Texture* texture,SDL_Surface* surface,float angle)
{
    draw(renderer,texture);

    SDL_Event event;

    while(1)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                return;

            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    draw(renderer,texture);
                }
                break;
            case SDL_KEYDOWN:
                if (event.type == KEYDOWN)
                { 
                    SDL_Surface *res = SDL_RotationCentrala(surface,angle);
                    const char *img_P = argv[1];
                    SDL_Texture* texture= IMG_LoadTexture(renderer,img_P);
                    if(texture == NULL)
                        errx(EXIT_FAILURE, "%s", SDL_GetError());

                    SDL_Surface* surface= load_image(img_P);

                    // Gets the width and the height of the texture.
                    int w = surface->w;
                    int h = surface->h;

                    if (SDL_QueryTexture(texture, NULL, NULL, &w, &h) != 0)
                        errx(EXIT_FAILURE, "%s", SDL_GetError());

                    draw(renderer,texture);

                }
        }
    }
    SDL_Quit();
}

SDL_Surface* load_image(const char* path)
{
    SDL_Surface* new_surface = IMG_Load(path);
    SDL_Surface* format = SDL_ConvertSurfaceFormat( new_surface, SDL_PIXELFORMAT_RGB888, 0);
    return format;
}

int main(int argc, char** argv)
{
    // Checks the number of arguments.
    if (argc != 2)
        errx(EXIT_FAILURE, "Usage: image-file");

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());


    SDL_Window* window = SDL_CreateWindow("Display", 0, 0, INIT_WIDTH, INIT_HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    // - Create a window.
    // - Create a renderer.
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    

   
    

    // - Create a texture from the image.
    const char *img_P = argv[1];
    SDL_Texture* texture= IMG_LoadTexture(renderer,img_P);
    if(texture == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    SDL_Surface* surface= load_image(img_P);

    // Gets the width and the height of the texture.
    int w = surface->w;
    int h = surface->h;

    if (SDL_QueryTexture(texture, NULL, NULL, &w, &h) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());



    SDL_SetWindowSize(window, w, h);
    
    float angle = 30;
    // - Dispatch the events.
    event_loop(renderer,texture,surface,angle);


    // - Destroy the objects.i
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
