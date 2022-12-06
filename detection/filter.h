#ifndef FILTER_H
#define FILTER_H

#include "LineParameter.h"
struct LineParameter* FilterLines(struct LineParameter* DetectedLines, float rho_threshold, float theta_threshold, int* nb_lines);
#endif
