#include <gtk/gtk.h>

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "solver/solver.h"
#include "solver/parser.h"
#include "image_processing/processing_final.h"
#include "image_rotation/rotation.h"
#include "detection/detection.h"
#include "interface/display.h"



int grille[9*9] = { 0, 0, 6, 2, 0, 0, 0, 8, 0 ,
      	   		0, 0, 8, 9, 7, 0, 0, 0, 0 ,
      	   		0, 0, 4, 8, 1, 0, 5, 0, 0 ,
           		0, 0, 0, 0, 6, 0, 0, 0, 2 ,
           		0, 7, 0, 0, 0, 0, 0, 3, 0 ,
           		6, 0, 0, 0, 5, 0, 0, 0, 0 ,
           		0, 0, 2, 0, 4, 7, 1, 0, 0 ,
           		0, 0, 3, 0, 2, 8, 4, 0, 0 ,
           		0, 5, 0, 0, 0, 1, 2, 0, 0 };



GtkWidget *spin;
GtkWidget *window;
GtkWidget *window1;
GtkWidget *label;
GtkWidget *file1;
GtkWidget *image;
GdkPixbuf *pixbuf;
GtkWidget *buton_next;
GtkWidget *buton_preview;
double degree = 0;
int boo_degree = 0;
int state = 0;




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


void exit_app1()
{
	printf("Button clicked : exit_app1");
	gtk_main_quit();


}

void exit_app()
{
	printf("Button clicked\n");

	gtk_main_quit();
    

}

void button_cliked()
{
	exit_app();
}

void button_label()
{
	GtkBuilder *builder;
	gtk_widget_hide(window);

	builder = gtk_builder_new();

	gtk_builder_add_from_file(builder,"interface/inter.glade",NULL);

	window1 = GTK_WIDGET(gtk_builder_get_object(builder,"Main_theme"));
	file1 = GTK_WIDGET(gtk_builder_get_object(builder,"file1"));
	image = GTK_WIDGET(gtk_builder_get_object(builder,"image_grille"));
    buton_next = GTK_WIDGET(gtk_builder_get_object(builder,"button_next"));
    buton_preview = GTK_WIDGET(gtk_builder_get_object(builder,"button_preview"));
    spin = GTK_WIDGET(gtk_builder_get_object(builder,"spin"));
    label = GTK_WIDGET(gtk_builder_get_object(builder,"error"));
    state = 1;
	gtk_builder_connect_signals(builder,NULL);

	g_object_unref(builder);

	gtk_widget_show_all(window1);




}


char *on_file1_file_set(GtkFileChooserButton *f)
{
    
    printf("%f\n",degree); 
	char *res = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(f));/*
    if(boo_degree)
    {
        int a = princip(res,(float)degree);
        res  = "image_rotation/image_rot";
        if(!a)
            return NULL;
    }
    else
    {
        return NULL;
    }*/
	printf("filename : %s\n",res);
    int w = 0;
    int h = 0;
    int *mat = image_processing(res,&w,&h);
    /*for (int i = 0; i < w*h;i++)
    {
        if (i % w == 0)
            printf("%d\n",mat[i]);
        else
            printf("%d",mat[i]);
    }*/
    int** cases = detection(mat, w, h);
	pixbuf = gdk_pixbuf_new_from_file(res,NULL);
	gdk_pixbuf_scale_simple(pixbuf,50,50,GDK_INTERP_BILINEAR);
	gtk_image_set_from_pixbuf(GTK_IMAGE(image),pixbuf);
    gdk_pixbuf_save(pixbuf,"base_grille.png","png",NULL,NULL);
    printf("pass\n"); 
    New_img(grille);
	return res;
}



void button_next()
{
    printf("%d\n",state);
	if(state == 1)
	{
		state += 1;
		pixbuf = gdk_pixbuf_new_from_file("grille.bmp",NULL);
	    gtk_image_set_from_pixbuf(GTK_IMAGE(image),pixbuf);

	}
    else if(state == 2)
	{
		state += 1;
		pixbuf = gdk_pixbuf_new_from_file("grille_g.bmp",NULL);
	    gdk_pixbuf_scale_simple(pixbuf,50,50,GDK_INTERP_BILINEAR);
	    gtk_image_set_from_pixbuf(GTK_IMAGE(image),pixbuf);
        
	}
    else if (state < 3)
        state+=1;


}

void button_preview()
{
    printf("%d\n",state);

    if(state == 1)
	{
		state -= 1;
		pixbuf = gdk_pixbuf_new_from_file("base_grille.png",NULL);
	    gdk_pixbuf_scale_simple(pixbuf,50,50,GDK_INTERP_BILINEAR);
	    gtk_image_set_from_pixbuf(GTK_IMAGE(image),pixbuf);

	}
    else if(state == 2)
	{
		state -= 1;
		pixbuf = gdk_pixbuf_new_from_file("grille.bmp",NULL);
	    gdk_pixbuf_scale_simple(pixbuf,50,50,GDK_INTERP_BILINEAR);
	    gtk_image_set_from_pixbuf(GTK_IMAGE(image),pixbuf);
	}
    else if (state > 0)
    {
        state-=1;
    }
}

void spin_boutton()
{
    degree = gtk_spin_button_get_value (GTK_SPIN_BUTTON(spin));
    boo_degree = 1;

}
