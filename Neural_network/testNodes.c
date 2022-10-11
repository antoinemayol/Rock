#include <stdio.h>
#include "nerons.h"

int main()
{
	node tmp = give_node(2,3,4,6,5,"test");
	printf("%s",tmp.name);
}
