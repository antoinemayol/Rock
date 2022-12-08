#pragma once


double sig(double z);
double Dsig(double z);
void mix(int *array, size_t n);
void proceed(int limit,char* num);
Uint32 get_pixel2(SDL_Surface *surface, int x, int y);
double* create_ar(SDL_Surface *surface);
int get_maxi(double* arr);
double randfrom(double min, double max);
double** get_trainset(char* num);
void set_scratch();

int forward(double* input);
int* final_fun(double** inputs);

