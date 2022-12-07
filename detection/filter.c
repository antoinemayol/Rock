#include "filter.h"
#include "list.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "LineParameter.h"
#include "list_line.h"
#include "print_function.h"

float __abs(float x);
struct LineParameter* supp_equivalent(struct LineParameter* DetectedLines, float theta_threshold, int* nb_lines);

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
    /*for(int i = 0; i < *nb_lines; i++)
    {
        free_all(similar_lines + i);
    }*/
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
    struct LineParameter* FinalLines = supp_equivalent(FilteredLines, theta_threshold, nb_lines);
    return FinalLines;
}

int get_most_used_angle(struct LineParameter* DetectedLines, int nb_lines)
{
    int* angles = malloc(sizeof(int)*91);
    for(int i = 0; i < nb_lines; i++)
        angles[i] = 0;
    for(int i = 0; i < nb_lines; i++)
        angles[(int)DetectedLines[i].angle] +=1;

    int max = 0;
    for(int i = 1; i < nb_lines; i++)
        if(angles[i] >= angles[max])
            max = i;
    free(angles);
    return max;
}

struct LineParameter* supp_equivalent(struct LineParameter* DetectedLines, float theta_threshold, int* nb_lines)
{
   int max_angle = get_most_used_angle(DetectedLines, *nb_lines);
   struct LineParameter* final = malloc(sizeof(struct LineParameter)*4);

    struct listl* hori_list =malloc(sizeof(struct listl));
    listl_init(hori_list);
    struct listl* verti_list =malloc(sizeof(struct listl));
    listl_init(verti_list);

    for(int i = 0; i < *nb_lines; i++)
    {
        int angle = (int)DetectedLines[i].angle;
        if(DetectedLines[i].angle < 0 || DetectedLines[i].angle > 90)
            angle = -1;
        if(abs(max_angle - angle) <= theta_threshold || abs(abs(max_angle-90) - angle) <= theta_threshold)
        {
           
           struct listl* elm = malloc(sizeof(struct listl));;
           elm->data = DetectedLines +i;
           if(angle < 45 && angle >=0)
           {
                listl_insert(hori_list, elm);
           }
           else if(angle >= 45 && angle <=90)
           {
                listl_insert(verti_list, elm);
           }
        }

    }
    *(final ) = *get_min(hori_list);
    *(final + 1) = *get_min(verti_list);
    *(final + 2) = *get_max(hori_list);
    *(final + 3) = *get_max(verti_list);
    free_alll(hori_list);
    free_alll(verti_list);
   return final;
}

float __abs(float x)
{
    return x>=0?x:-x;
}
