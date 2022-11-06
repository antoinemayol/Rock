#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
 
SDL_Surface* affichage;
 
void initSDL(void);
void attendreTouche(void);
 
int main(int argc, char** argv)
{
  initSDL();
  attendreTouche();
  return EXIT_SUCCESS;
}
 
void initSDL(void)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Erreur à l'initialisation de la SDL : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
 
  atexit(SDL_Quit);
  affichage = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
 
  if (affichage == NULL) {
    fprintf(stderr, "Impossible d'activer le mode graphique : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
 
  SDL_WM_SetCaption("Mon premier programme SDL", NULL);
}
 
void attendreTouche(void)
{
  SDL_Event event;
 
  do
    SDL_WaitEvent(&event);
  while (event.type != SDL_QUIT && event.type != SDL_KEYDOWN);
}
