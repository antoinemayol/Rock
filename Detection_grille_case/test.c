#include <stdio.h>
#include "components_connexes.h"

int main()
{
    int lenght= 6;
    int width= 6;
    int input[6][6] = {
        {0,0,0,0,0,0},
        {0,1,0,1,0,0},
        {0,1,1,1,0,0},
        {0,0,0,0,0,0},
        {0,0,1,0,1,0},
        {0,1,1,1,1,0}};
    int out[6][6] ={0};
    connected_components(lenght,width,input,out);
    print_mat(lenght, width, out);
    return 0;
}

