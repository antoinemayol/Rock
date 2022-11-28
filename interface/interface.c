#include <gtk/gtk.h>
#include <stdio.h>

GtkWidget *window;
GtkLabel *label;
GtkWidget *file1;



int main (int argc, char *argv[])
{
	//Initialize gtk
	gtk_init(&argc,&argv);

	
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

	builder = gtk_builder_new();

	gtk_builder_add_from_file(builder,"inter.glade",NULL);

	window = GTK_WIDGET(gtk_builder_get_object(builder,"Main_theme"));
	file1 = GTK_WIDGET(gtk_builder_get_object(builder,"file1"));

	gtk_builder_connect_signals(builder,NULL);

	g_object_unref(builder);

	gtk_widget_show_all(window);

}

char *on_file1_file_set(GtkFileChooserButton *f)
{
	char *res = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(f));
	printf("filename : %s\n",res);
}
