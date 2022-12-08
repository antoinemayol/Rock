#include "matrix.h"

typedef struct{
    int input;
    int hidden;
    int output;
    double lr;
    matrix* hidden_w;
    matrix* output_w;
}neuralnet;

neuralnet* create_neur(double lr, int in, int hid, int out);
void train_net(neuralnet* neu, matrix* in, matrix* out);
void train_xor();
