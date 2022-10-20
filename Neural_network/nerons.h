typedef struct node 
{
	char* name;
	double weight;
	double x1;
	double x2;
	double w1;
	double w2;
	char *path;
} node;

node give_node(double wht, double _x1, double _x2, double _w1, double _w2, char* _name);
void concat_path(char* res, char* s1, char* s2, char* s3, int maxpath);
void refresh(node *n);
node fromfile(char* path);
