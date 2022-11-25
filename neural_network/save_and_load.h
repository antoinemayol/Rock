#pragma once
#include <string.h>

void concat_path(char* res, char* s1, char* s2, char* s3, char* s4, int maxpath);
void save(double *a, int i, size_t len);
void add_one(double** a, double b, size_t* len);
double* load(char* path, size_t* len);
