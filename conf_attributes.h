#ifndef LAB3_CONF_ATTRIBUTES_H
#define LAB3_CONF_ATTRIBUTES_H

#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

struct IntegralAttributes {
    std::map<std::string, std::vector<double> > params;
    double absolute_error;
    double relative_error;
    double NThreads;
    double x1;
    double x2;
    double y1;
    double y2;
};

std::vector<double> split_and_double(const std::string &str, const char &delim = ',');

IntegralAttributes *get_intArgs(const std::string &filename);
#endif //LAB3_CONF_ATTRIBUTES_H
