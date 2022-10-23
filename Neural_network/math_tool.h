#pragma once
#include <string.h>

double sum(int s_index, double list[], size_t len);
double logloss(double as[], double ys[], size_t m);
double perceptron(double x1, double x2, double b, double w1, double w2);
double sigmoide(double z);
