
#include <math.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int INIT_WIDTH = 640;
const int INIT_HEIGHT = 400;


/*Determine pixel value at position x,y*/
Uint32  SDL_LirePixel(SDL_Surface* surface, int x, int y)
{
  int bpp = surface->format->BytesPerPixel;
 
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
 
  switch(bpp)
  {
  		case 1:
        	return *p;
        case 2:
            return *(Uint16 *)p;
        case 3:
           	if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            	return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        case 4: 
            return *(Uint32 *)p;
       	default:
        	return 0;
  } 
 
}
 
 
/*Write pixels to position x,y*/
void SDL_EcrirePixel(SDL_Surface* surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel; 
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp; 
 
 
    switch(bpp) 
	{ 
    	case 1: 
        	*p = pixel; 
        	break; 
 
    	case 2: 
        	*(Uint16 *)p = pixel; 
        	break; 
 
    	case 3: 
        	if(SDL_BYTEORDER == SDL_BIG_ENDIAN) 
			{ 
            	p[0] = (pixel >> 16) & 0xff; 
            	p[1] = (pixel >> 8) & 0xff; 
            	p[2] = pixel & 0xff; 
        	} 
			else 
			{ 
            p[0] = pixel & 0xff; 
            p[1] = (pixel >> 8) & 0xff; 
            p[2] = (pixel >> 16) & 0xff; 
        	} 
        	break; 
 
    	case 4: 
        	*(Uint32 *)p = pixel; 
        	break; 
    	}  
 
}
 
/*Proceed the rotation from an angle in degree, automatically allocate memory*/
SDL_Surface* SDL_RotationCentrala(SDL_Surface* origine, float angle)
{
	SDL_Surface* destination;
	int i;
	int j;
	Uint32 couleur;
	int mx, my;

	int bx, by;
	float angle_radian;

	/* Determine value of angle in radian */
	angle_radian = -angle * M_PI / 180.0;

	/* 
	 * Allocate memory to the destination, warning, 
	 * the surface has the same size
	 */
	destination = SDL_CreateRGBSurface(SDL_SWSURFACE, origine->w, origine->h, origine->format->BitsPerPixel,
					origine->format->Rmask, origine->format->Gmask, origine->format->Bmask, origine->format->Amask);

	/*We verify that memory has been allocated*/
	if(destination==NULL)
		return NULL;

	/*To simplify notation*/
	mx = origine->w/2;
	my = origine->h/2;

	for(j=0;j<origine->h;j++)
		for(i=0;i<origine->w;i++)
		{
			/* We determine pixel value that fit better to the position i, j*/

			/*We determine the best position on the origin surface by applying
			* an inverse rotation matrix
			*/

			bx = (int) (cos(angle_radian) * (i-mx) + sin(angle_radian) * (j-my)) + mx;
			by = (int) (-sin(angle_radian) * (i-mx) + cos(angle_radian) * (j-my)) + my;

			/* We verify that we don't get out of bounds*/

			if (bx>=0 && bx< origine->w && by>=0 && by< origine->h)
			{
				couleur = SDL_LirePixel(origine, bx, by);
				SDL_EcrirePixel(destination, i, j, couleur);
			}
		}
	return destination;
}


//take a new SDL_Surface from an image to use her
SDL_Surface* load_image1(const char* path)
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

int princip(char* argv,float angle)
{
    // Checks the number of arguments.



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
    const char *img_P = argv;
    SDL_Texture* texture= IMG_LoadTexture(renderer,img_P);
    if(texture == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    SDL_Surface* surface= load_image1(img_P);

    // Gets the width and the height of the texture.
    int w = surface->w;
    int h = surface->h;

    if (SDL_QueryTexture(texture, NULL, NULL, &w, &h) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());



    SDL_SetWindowSize(window, w, h);
    

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
