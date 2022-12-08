#include "matrix.h"

int main()
{
    matrix* m1 = create_mat(2,2);
    m1->inputs[0][0] = 1.0f;
    m1->inputs[0][1] = 3.0f;
    m1->inputs[1][0] = 6.0f;
    m1->inputs[1][1] = 2.0f;

    matrix* m2 = create_mat(2,2);
    m2->inputs[0][0] = 1.0f;
    m2->inputs[0][1] = 3.0f;
    m2->inputs[1][0] = 5.0f;
    m2->inputs[1][1] = 8.0f;

    printf("m1 = \n");
    print_m(m1);

    printf("\n");

    printf("m2 = \n");
    print_m(m2);

    printf("\n");
    
    printf("m1 transpose\n");
    matrix* trans_m1 = trans_m(m1);
    print_m(trans_m1);

    printf("\n");


    printf("m1 + m2\n");
    matrix* add_m1_m2 = add_m(m1,m2);
    print_m(add_m1_m2);

    printf("\n");

    printf("m1 - m2\n");
    matrix* sub_m1_m2 = sub_m(m1,m2);
    print_m(sub_m1_m2);

    printf("\n");

    printf("m1 . m2\n");
    matrix* dot_m1_m2 = dot_m(m1,m2);
    print_m(dot_m1_m2);

    printf("\n");

    printf("m1 * m2\n");
    matrix* mult_m1_m2 = mult_m(m1,m2);
    print_m(mult_m1_m2);
}
