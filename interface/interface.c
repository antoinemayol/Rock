#include <gtk/gtk.h>
#include <stdio.h>

GtkWidget *window;
GtkLabel *label;



int main (int argc, char *argv[])
{
	//Initialize gtk
	gtk_init(&argc,&argv);

	//gtk bulder
	GtkBuilder *builder;

	builder = gtk_builder_new();
	
	gtk_builder_add_from_file(builder,"inter.glade", NULL); //load our ui file
	
	window = GTK_WIDGET(gtk_builder_get_object(builder,"MyWindow"));
	label = GTK_LABEL(gtk_builder_get_object(builder,"MyLabel"));

	gtk_builder_connect_signals(builder,NULL);

	g_object_unref(builder);
															
	
	//show the window
	gtk_widget_show_all(window);
	
	//run the main loop
	gtk_main();

}

void exit_app()
{
	printf("Exit function \n");
	gtk_main_quit();
}

void button_cliked()
{
	printf("Button clicked\n");
	
	exit_app();

}

void button_label()
{
	printf("button_label_cliked\n");
	gtk_label_set_text(label,"Love You Mate");
}
