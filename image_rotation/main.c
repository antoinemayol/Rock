#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "rotation.h"

//HEADER
//
void draw(SDL_Renderer* renderer, SDL_Texture* texture);
void draw2(SDL_Surface *surface);
void event_loop(SDL_Renderer* renderer, SDL_Texture* texture,SDL_Surface* surface,float angle);
SDL_Surface* load_image(const char* path);
//initialisation taille du display
//
const int INIT_WIDTH = 640;
const int INIT_HEIGHT = 400;
float INIT_ANGLE = 45;

//permet de afficher ou de reaficher l'image
void draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer,texture,NULL,NULL);
    SDL_RenderPresent(renderer);
}

void draw2(SDL_Surface *surface)
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
   //event_loop(renderer, texture,surface;
   //test_loop(renderer, texture, processed);
   
   //Destroying objects
   SDL_DestroyRenderer(renderer);
   SDL_DestroyTexture(texture);
   //SDL_DestroyTexture(grayscale);
   SDL_DestroyWindow(window);
   SDL_Quit();

   

}
   
//check all the different event to update our image
void event_loop(SDL_Renderer* renderer, SDL_Texture* texture,SDL_Surface* surface,float angle)
{
    
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
                 SDL_Surface *res = SDL_RotationCentrala(surface,angle);
                 SDL_Texture* te = SDL_CreateTextureFromSurface(renderer, res);
                 draw(renderer,te);

        }
    }
    SDL_Quit();
}

//take a new SDL_Surface from an image to use her
SDL_Surface* load_image(const char* path)
{
    SDL_Surface* new_surface = IMG_Load(path);
    SDL_Surface* format = SDL_ConvertSurfaceFormat( new_surface, SDL_PIXELFORMAT_RGB888, 0);
    return format;
}

//change the name of the new file
char *name_filled(char* img_name)
{
    int i = 0;
    for(;img_name[i] != '\0';i++);
    char *res = malloc(sizeof(int)*i+8);
    char *end = "Rot.bmp";
    int y = 0;
    for(;img_name[y]!= '\0';y++)
    {
        res[y]=img_name[y];
    }
    y++;
    int z =0;
    while(z < 8)
    {
        res[y]= end[z];
        y++;
        z++;
    }
 
    return res;

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
    
    float angle = INIT_ANGLE;
    // - Dispatch the events.
    //event_loop(renderer,texture,surface,angle);

    SDL_Surface *result = SDL_RotationCentrala(surface,angle);

    //char *res = name_filled(argv[1]);
    if(SDL_SaveBMP(result,"imageRot.bmp") != 0)
    {
        printf("SDL_SaveBMP failed: %s\n", SDL_GetError());
    }



    // - Destroy the objects.i
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
