#include <string.h>

typedef struct Brain{
	double* array;
	size_t len;
	size_t index;
}Brain;

Brain get_empty();
void add_b(Brain *b, double d);
void add_array(Brain *b, double* a, size_t len_a);
void save_brain(Brain b, int i);
Brain load_brain(char* path);
Brain* make_neuronal(size_t* count);
