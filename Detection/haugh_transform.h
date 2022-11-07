#ifndef HAUGH_TRANSFORM_H
#define HAUGH_TRANSFORM_H

int *hough_transform(int h, int w, int *mat, int *hough_val);
void print_graph(int l, int w, int *matrix);
int get_max_hough_occ(int l, int w, int *hough);
void get_equation(int roh, int phi, int *hough_val, int *equation);
void hough_traitement(int l, int w, int *mat);

#endif
