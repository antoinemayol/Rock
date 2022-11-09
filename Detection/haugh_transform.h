#ifndef HAUGH_TRANSFORM_H
#define HAUGH_TRANSFORM_H

int *hough_transform(int h, int w, int *mat, int *hough_val);
void print_graph(int l, int w, int *matrix);
void print_case(int **coo, int* mat, int width);
int get_max_hough_occ(int l, int w, int *hough);
int** get_equation(int roh, int phi, int *hough_val, int *equation);
int** hough_traitement(int l, int w, int *mat);
int is_val_in_arr(int x, int* arr,int len);
int** extract_intersection(int* horizontal_equ, int* vertical_equ, int lenh, int lenv);
int deg_approximation(int deg,int biais, int cible);
void stock_cases(int** coo, int* matrix, int width, int** cases);

#endif
