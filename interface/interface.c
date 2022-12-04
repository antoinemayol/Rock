#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

GtkWidget *window;
GtkWidget *window1;
GtkWidget *label;
GtkWidget *file1;
GtkWidget *image;
GdkPixbuf *pixbuf;
int state = 1;




int main (int argc, char *argv[])
{
	//Initialize gtk
	gtk_init(&argc,&argv);

	GtkBuilder *builder;
	
	builder = gtk_builder_new();
	
	gtk_builder_add_from_file(builder,"inter.glade", NULL); //load our ui file
	
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

	gtk_builder_add_from_file(builder,"inter.glade",NULL);

	window1 = GTK_WIDGET(gtk_builder_get_object(builder,"Main_theme"));
	file1 = GTK_WIDGET(gtk_builder_get_object(builder,"file1"));
	image = GTK_WIDGET(gtk_builder_get_object(builder,"image_grille"));
	
	

	gtk_builder_connect_signals(builder,NULL);

	g_object_unref(builder);

	gtk_widget_show_all(window1);




}

char *on_file1_file_set(GtkFileChooserButton *f)
{
	char *res = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(f));
	printf("filename : %s\n",res);
	pixbuf = gdk_pixbuf_new_from_file(res,NULL);
	gdk_pixbuf_scale_simple(pixbuf,50,50,GDK_INTERP_BILINEAR);
	gtk_image_set_from_pixbuf(GTK_IMAGE(image),pixbuf);

	return res;
}

void button_next()
{
	if(state == 1)
	{
		state += 1;
		//afficher grille pas completé
	}
	if(state == 2)
	{
		state += 1;
		//afficher grille completé
	}

}
