#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../solver/solver.h"


/*

int grille[9*9] = { 0, 0, 6, 2, 0, 0, 0, 8, 0 ,
      	   		0, 0, 8, 9, 7, 0, 0, 0, 0 ,
      	   		0, 0, 4, 8, 1, 0, 5, 0, 0 ,
           		0, 0, 0, 0, 6, 0, 0, 0, 2 ,
           		0, 7, 0, 0, 0, 0, 0, 3, 0 ,
           		6, 0, 0, 0, 5, 0, 0, 0, 0 ,
           		0, 0, 2, 0, 4, 7, 1, 0, 0 ,
           		0, 0, 3, 0, 2, 8, 4, 0, 0 ,
           		0, 5, 0, 0, 0, 1, 2, 0, 0 };*/

int pos[9] = {8,112,216,324,428,532,640,744,848};


// Updates the display.
//
// renderer: Renderer to draw on.
// texture: Texture that contains the image.
/*
void draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

// Event loop that calls the relevant event handler.
// renderer: Renderer to draw on.
// texture: Texture to display.
void event_loop(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_Event event;
    draw(renderer,texture);
    while(1)
    {
        SDL_WaitEvent(&event);

        switch(event.type)
        {
            case SDL_QUIT:
                return;

            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    draw(renderer,texture);
                }
                break;
        }
    }
}*//*
//______________________________________________________________________________________________________________________________
int absentOnRow (int k, int *grid, int i)
{
	for(int j = 0; j < 9;j++)

		if(grid[i*9+j] == k)
			return 0;
	}
	return 1;
}

//Check if the value k are on the col
int absentOnCol (int k, int *grid, int j) 
{
    for(int i = 0; i < 9;i++)
	{
		if(grid[i*9+j] == k)
			return 0;
	}
	return 1;
}

//Check if the value k are on the square
int absentOnBloc (int k, int *grid, int i, int j)
{
	i -= i%3;
	j -= j%3;
	for(int y = i; y < i+3 && y < 9;y++)
	{
		for(int z = j; z < j+3 && z< 9;z++)
		{
			if(grid[y*9+z] == k)
				return 0;
		}
	}
	return 1;
}

int backtracking(int *grid,int position)
{
		//We see if the position is at the end of the matrice
		if (position > 80)
				return 1;
		
		//We initialize the variable i and j with position
		int i = position / 9;
		int j = position % 9;
		
			
		if(grid[i*9+j] != 0)
		{
			return backtracking(grid,position + 1);
		}
		
		//Start the backtracking with a variable that can take all the different value in a sudoku
		for(int k = 1; k <= 9;k++)
		{
			if(absentOnRow(k,grid,i) && absentOnCol(k,grid,j) && absentOnBloc(k,grid,i,j))
			{
				grid[i*9+j] = k;

				if(backtracking(grid,position + 1))
						return 1;
			}
		}
			
		grid[i*9+j] = 0;
		return 0;
}*/

//______________________________________________________________________________________________________________________________________

SDL_Texture *change_board(int *board,int state, SDL_Surface *surface_p,SDL_Renderer *renderer)
{
	SDL_Texture *newT;
	SDL_Surface *surface_i;
	SDL_Rect dstrect;

	if(state == 2)
	{
		int bb[81];
		memcpy(bb, board, 81 * sizeof(int));
		backtracking(bb,0);
		int j = 0;
		while(j < 81)
		{
			bb[j] -= board[j];

			if(bb[j] != 0)
			{

				char x[2];

				x[0] = bb[j] + 48;
				x[1] = '\0';

				char *target = malloc(sizeof(char)*40);

				strcpy(target,"interface/data/num_");
				strcat(target,x);
				strcat(target,"g.png");


				surface_i = IMG_Load(target);

				dstrect.x = pos[j%9];
				dstrect.y = pos[j/9];




				SDL_BlitSurface(surface_i,NULL,surface_p,&dstrect);

				newT = SDL_CreateTextureFromSurface(renderer,surface_p);
				free(target);

			}
			j+=1;
		}
	}

	int i = 0;

	while(i<81)
	{
        
		if(board[i] != 0)
		{

			char x[2];

			x[0] = board[i] + 48;
			x[1] = '\0';

			char *target = malloc(sizeof(char)*40);


			strcpy(target,"interface/data/num_");
			strcat(target,x);
			strcat(target,".png");


			surface_i = IMG_Load(target);

			dstrect.x = pos[i%9];
			dstrect.y = pos[i/9];



			SDL_BlitSurface(surface_i,NULL,surface_p,&dstrect);

			newT = SDL_CreateTextureFromSurface(renderer,surface_p);


            free(target);
		}
	    i+=1;
	}

	return newT;

}

void New_img(int *grille)
{

    // - Initialize the SDL.
    //if (SDL_Init(SDL_INIT_VIDEO) != 0)
        //errx(EXIT_FAILURE, "%s", SDL_GetError());

    // - Create a window.
    SDL_Window* window = SDL_CreateWindow("Image", 0, 0,0,0,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (window == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    // - Create a renderer.
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());


    // - Create a texture from the image.
    SDL_Texture* texture;/*   = IMG_LoadTexture(renderer, "data/blank_grid.png");
    if(texture == NULL)
        errx(EXIT_FAILURE, "%s",SDL_GetError());

    // Gets the width and the height of the texture.
    int w, h;
    if (SDL_QueryTexture(texture, NULL, NULL, &w, &h) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    // - Resize the window according to the size of the image.
    SDL_SetWindowSize(window, w, h);*/

	SDL_Surface *surface = IMG_Load("interface/data/blank_grid.png");

	texture = change_board(grille,1,surface,renderer);


	SDL_SaveBMP(surface,"grille.bmp");

    texture = change_board(grille,2,surface,renderer);

    SDL_SaveBMP(surface,"grille_g.bmp");
    //event_loop(renderer,texture);


    // - Destroy the objects.
    //SDL_DestroyTexture(texture);
    //SDL_DestroyRenderer(renderer);
    //SDL_DestroyWindow(window);
    SDL_Quit();
    printf("smash\n");

}
