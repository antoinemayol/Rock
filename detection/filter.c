#include "filter.h"
#include "list.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "LineParameter.h"
float __abs(float x);
int get_most_used_angle(struct LineParameter* DetectedLines, int nb_lines);

struct LineParameter* FilterLines(struct LineParameter* DetectedLines, float rho_threshold, float theta_threshold, int* nb_lines)
{
    struct list* similar_lines = malloc(sizeof(struct list)**nb_lines);
    for(int i = 0; i <* nb_lines; i++)
        list_init(similar_lines + i);
    for(int i = 0; i <* nb_lines; i++)
        for(int j = 0; j <* nb_lines; j++)
            if(i != j)
            {
                float theta_i = DetectedLines[i].angle;
                float theta_j = DetectedLines[j].angle;
                float rho_i = DetectedLines[i].distance;
                float rho_j = DetectedLines[j].distance;
                if(__abs(rho_i - rho_j) < rho_threshold && __abs(theta_i - theta_j) < theta_threshold)
                {
                    struct list* elm = malloc(sizeof(struct list));
                    elm->data = j;
                    list_push_front(similar_lines+i, elm);
                }
            }
    int* indices = malloc(sizeof(int)**nb_lines);
    int max_len = 1;
    int k = 0;
    for(int i = 0; i <* nb_lines; i++)
    {
        *(indices + i) = i;
        int l = list_len(similar_lines + i);
        if(l>max_len)
            max_len = l;
    }
    for(int i = 1; i <=max_len && k < *nb_lines; i++)
        for(int j = 0; j < *nb_lines && k <* nb_lines; j++)
        {
            if(list_len(similar_lines + j) == (size_t)i)
            {
                *(indices + k) = j;
                k++;
            }
        }
   

    int* line_flags = malloc(sizeof(int)**nb_lines);
    for(int i = 0; i < *nb_lines; i++)
        *(line_flags + i) = 1;
    for(int i = 0; i < *nb_lines - 1; i++)
        if(line_flags[indices[i]])
        {
            for(int j = i + 1; j < *nb_lines; j++)
                if(line_flags[indices[j]])
                {
                    float theta_i = DetectedLines[indices[i]].angle;
                    float theta_j = DetectedLines[indices[j]].angle;
                    float rho_i = DetectedLines[indices[i]].distance;
                    float rho_j = DetectedLines[indices[j]].distance;
                    if(__abs(rho_i - rho_j) < rho_threshold && __abs(theta_i - theta_j) < theta_threshold)
                        line_flags[indices[j]] = 0;
                }
        }
    free(indices);
    struct LineParameter* FilteredLines = malloc(sizeof(struct LineParameter));;
    int nb_new_lines = 0;
    for(int i = 0; i < *nb_lines; i++)
        if(line_flags[i])
        {
            nb_new_lines++;
            FilteredLines = realloc(FilteredLines,sizeof(struct LineParameter)*nb_new_lines);
            *(FilteredLines + nb_new_lines - 1) = DetectedLines[i];
        }
    free(line_flags);
    *nb_lines = nb_new_lines;
    printf("anglesmax:%d\n",get_most_used_angle(DetectedLines, *nb_lines));
    return FilteredLines;
}

void supp_equivalent(struct LineParameter* DetectedLines, float rho_threshold, float theta_threshold, int* nb_lines)
{
   return; 
}

int get_most_used_angle(struct LineParameter* DetectedLines, int nb_lines)
{
    int* angles = calloc(0,sizeof(int)*91);
    for(int i = 0; i < nb_lines; i++)
        angles[(int)(DetectedLines + i)->angle] +=1;

    int max = 0;
    for(int i = 1; i < nb_lines; i++)
        if(angles[i] >= angles[max])
            max = i;
    free(angles);
    return max;
}

float __abs(float x)
{
    return x>=0?x:-x;
}
