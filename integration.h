#ifndef LAB3_INTEGRATION_H
#define LAB3_INTEGRATION_H

#include <vector>
#include <cmath>

#include "conf_attributes.h"

double
langermann_func(int m, std::vector<double> a1, std::vector<double> a2, std::vector<double> c, double x1, double x2);

double simple_integrate(double (*func)(int, std::vector<double>, std::vector<double>, std::vector<double>, double,
                                     double), IntegralAttributes &args, double x1, double x2, double dx_dy);

#endif //LAB3_INTEGRATION_H
