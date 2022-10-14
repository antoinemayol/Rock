#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "nerons.h"
#include <err.h>


//Retourne un neurones
node give_node(double wht, double _x1, double _x2, double _w1, double _w2, char* _name)
{
	node n;
	n.weight = wht;
	n.x1 = _x1;
	n.x2 = _x2;
	n.w1 = _w1;
	n.w2 = _w2;
	n.name = _name;

	size_t len = strlen(_name);
	n.path = malloc((len + strlen("neurones/") + strlen(".txt"))*sizeof(char));
	concat_path(n.path,"neurones/",_name,".txt",(len + 13));

	refresh(&n);	
	return n;
}


//permet de créer le chemin d'un noeud
void concat_path(char* res,char* s1, char* s2, char* s3, int maxpath)
{
	int k = 0;
	for(size_t i = 0; k < maxpath && s1[i] != '\0'; i++)
	{
		res[k]=s1[i];
		k+=1;
	}

	for(size_t i = 0; k < maxpath && s2[i] != '\0'; i++)
	{
		res[k]=s2[i];
		k+=1;
	}

	for(size_t i = 0; k < maxpath && s3[i] != '\0'; i++)
	{
		res[k]=s3[i];
		k+=1;
	}

}

//mets à jours les valeurs dans le fichier du noeud n
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

void fromfile(char* path)
{
	//node n;
	FILE *f = fopen(path,"r");
	if(f == NULL)
   	{
		errx(1,"can't open file !");
	}
		
	char *line =NULL;
	size_t len = 0;

	while(getline(&line, &len, f) != -1)
	{
		printf("line length : %zd\n",strlen(line));
	}

	fclose(f);
	free(line);
}
