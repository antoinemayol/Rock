#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>

SDL_Surface* load_image(const char* path)
{
    SDL_Surface* s = IMG_Load(path);
    SDL_Surface* surface = SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_RGB888, 0);
    SDL_FreeSurface(s);
    return surface;
}

void render(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

/*Loop for testing purposes --> Switches from original to processed image when pressing a key */
void test_loop(SDL_Renderer *renderer, SDL_Texture *colored, SDL_Texture *grayscale)
{
    SDL_Event event;
    SDL_Texture* t = colored;
    //draw(renderer, t);
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
                render(renderer, t);
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
                render(renderer, t);
                break;

            }
        }
    }
}

void event_loop(SDL_Renderer *renderer, SDL_Texture *texture)
{

    SDL_Event event;
    while (1)
    {
        SDL_WaitEvent(&event);
        render(renderer, texture);
        switch (event.type)
        {
            case SDL_QUIT:
            {
                return;
                break;
            }
            case SDL_WINDOWEVENT_RESIZED:
            {
                render(renderer, texture);
                break;
            }
        }
    }

}

int draw(SDL_Surface *surface)
{
    //Initializing and checking possible startup errors
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    SDL_Window* window= SDL_CreateWindow("Diplay", 0, 0, 640, 480, SDL_WINDOW_RESIZABLE);
    if(window == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
   //resizing
   int w = surface->w;
   int h = surface->h;
   SDL_SetWindowSize(window, w, h);
    
   //creating texture from image
   SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
   //SDL_Texture* processed =  SDL_CreateTextureFromSurface(renderer, surface);
   SDL_FreeSurface(surface);

   //calling the main loop
   event_loop(renderer, texture);
   //test_loop(renderer, texture, processed);
   
   //Destroying objects
   SDL_DestroyRenderer(renderer);
   SDL_DestroyTexture(texture);
   //SDL_DestroyTexture(grayscale);
   SDL_DestroyWindow(window);
   SDL_Quit();

   return EXIT_SUCCESS;

}
