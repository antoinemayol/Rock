#include <string.h>

char *getString(char *path);
void getSudok(char *s, int res[9*9]);
void file_to_sudok(char *path, int res[9*9]);
void sudok_to_file(int sudok[9*9],char* path);
void writeS(char* s, char* path);
char *ai_to_st(int sudok[9*9]);
