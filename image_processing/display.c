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
void test_loop(SDL_Renderer *renderer, SDL_Texture **textures, int steps)
{
    SDL_Event event;
    //draw(renderer, t)
    int i=0;
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
                render(renderer, textures[i]);
                break;
            }
            case SDL_KEYDOWN:
            {
                if(event.key.keysym.sym == SDLK_RIGHT)
                {
                    if(i < steps-1)
                    {
                        i++;
                    }
                    else
                    {
                        i=0;
                    }
                }
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    if(i > 0)
                    {
                        i--;
                    }
                    else
                    {
                        i=steps-1;
                    }
                }
                render(renderer, textures[i]);
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

/*Draws the final processed image using SDL */
int draw(SDL_Surface **surfaces, int steps)
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
   int w = surfaces[0]->w;
   int h = surfaces[0]->h;
   SDL_SetWindowSize(window, w, h);

   SDL_Texture **textures = malloc(sizeof(SDL_Texture*)*steps);
   //creating texture from image
   for(int i=0; i<steps; i++)
   {
        textures[i] =  SDL_CreateTextureFromSurface(renderer, surfaces[i]);
   }

   //calling the main loop
   test_loop(renderer, textures, steps);

   //Destroying objects
   SDL_DestroyRenderer(renderer);
   for(int i = 0; i<steps; i++)
   {
        SDL_DestroyTexture(textures[i]);
   }
   free(textures);
   //SDL_DestroyTexture(grayscale);
   SDL_DestroyWindow(window);
   SDL_Quit();

   return EXIT_SUCCESS;

}
