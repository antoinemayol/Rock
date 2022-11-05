#include <stdio.h>
#include "components_connexes.h"


int main()
{

    int lenght= 10;
    int width= 10;
    int input[10][10] = {
        {0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,1,1,1,0,1,0,1,0},
        {0,0,1,0,1,0,0,0,1,0},
        {0,0,1,1,1,1,1,0,1,0},
        {0,0,1,0,1,0,1,0,0,0},
        {0,0,1,1,1,1,1,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,1,1,0,0,0,0},
        {0,0,1,0,1,0,0,0,0,0}};


    connected_components(lenght,width,input);
    return 0;
}

