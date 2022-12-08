#ifndef HT_H
#define HT_H

#include "LineParameter.h"

struct LineParameter* HTLineDetection(int* BinaryImageDst, int* LineNumber, struct LineParameter* DetectedLine, int nHeight, int nWidth);
void HoughTransform_Line(int* BinaryImageDst, float MinAngle, float AngleInterval, int No_Angles, float MinDistance,  float DistanceInterval, int No_Distances, unsigned int** VoteTable, int nHeight, int nWidth );
void FindMaxVote(unsigned int** VoteTable, int No_Angles, int No_Distances, int* M, int* N);
int FindArrayMax(unsigned int* Array, int No_of_Element);
int Larger_in_Array(unsigned int* Array, int x, int y);

#endif
