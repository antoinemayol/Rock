#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "interface.h"

GtkWidget *window;
GtkWidget *window1;
GtkWidget *label;
GtkWidget *file1;
GtkWidget *image;
GdkPixbuf *pixbuf;
GtkWidget *buton_next;
GtkWidget *buton_preview;
int state = 0;

void save_board()
{
    SDL_Texture *texture;

    SDL_Window* window = SDL_CreateWindow("Image", 0, 0,0,0,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (window == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    // - Create a renderer.
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    SDL_Surface *surface = IMG_Load("data/blank_grid.png");

	texture = change_board(grille,1,surface,renderer);

	SDL_SaveBMP(surface,"grille.bmp");

    texture = change_board(grille,2,surface,renderer);

    SDL_SaveBMP(surface,"grille_g.bmp");

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;

}

int main (int argc, char *argv[])
{
	//Initialize gtk
	gtk_init(&argc,&argv);

	GtkBuilder *builder;

	builder = gtk_builder_new();

	gtk_builder_add_from_file(builder,"interface/inter.glade", NULL); //load our ui file
                                                            //
	window = GTK_WIDGET(gtk_builder_get_object(builder,"MyWindow"));

	gtk_builder_connect_signals(builder,NULL);

	g_object_unref(builder);

	//show the window
	gtk_widget_show_all(window);

	//run the main loop
	gtk_main();

}


