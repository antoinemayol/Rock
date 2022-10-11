#include <string.h>
#include <stdio.h>
#include "nerons.h"
#include <err.h>

node give_node(double wht, double _x1, double _x2, double _w1, double _w2, char* _name)
{
	node n;
	n.weight = wht;
	n.x1 = _x1;
	n.x2 = _x2;
	n.w1 = _w1;
	n.w2 = _w2;
	n.name = _name;
	strcat(n.path,"neurones/");
	strcat(n.path, _name);
	strcat(n.path,".txt");
	refresh(&n);
	return n;
}

void refresh(node *n)
{
	FILE *f = fopen(n->path,"w");

	if(f == NULL)
   	{
		errx(1,"can't open file !");
	}

	fprintf(f,"name : %s \n",n->name);
	fprintf(f,"weight : %f \n",n->weight);
	fprintf(f,"X1 : %f \n",n->x1);
	fprintf(f,"X2 : %f \n",n->x2);
	fprintf(f,"W1 : %f \n",n->w1);
	fprintf(f,"W2 : %f \n",n->w2);
	fclose(f);
}
