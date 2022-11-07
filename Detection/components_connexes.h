#ifndef COMPONENTS_CONNEXES_H
#define COMPONENTS_CONNEXES_H

void print_mat(int lenght, int width, int *matrix);
int get_obj_nb(int *equivalence);
void connected_components(int l, int w, int matrix[l][w]);
void get_partitioned_matrix(int l, int w,int matrix[l][w], int output[l][w]);
void apply_equivalence(int l, int w, int output[l][w], int *equivalence);

#endif
