#include "conf_attributes.h"

std::vector<double> split_and_double(const std::string &str, const char &delim) {
    std::vector<double> params;
    size_t current, prev = 0;
    current = str.find(delim);
    while (~current) {
        params.push_back(std::stod(str.substr(prev, current - prev)));
        prev = current + 1;
        current = str.find(delim, prev);
    }
    params.push_back(std::stod(str.substr(prev, current - prev)));
    return params;
}

IntegralAttributes *get_intArgs(const std::string &filename) {
/*You need to pass parameters in such way
 *  absolute_error;
    relative_error;
    NThreads;

    x1; - starting from x1
    x2; - ends with x1
    y1;
    y2;
*/
    auto *attributes = new IntegralAttributes;
    bool until_params = true;
    std::map<std::string, double *> conf_attributes{{"absolute_error",    &attributes->absolute_error},
                                                    {"relative_error",    &attributes->relative_error},
                                                    {"start_x",           &attributes->x1},
                                                    {"end_x",             &attributes->x2},
                                                    {"start_y",           &attributes->y1},
                                                    {"end_y",             &attributes->y2}};
    std::ifstream f(filename);
    std::string line;
    while (getline(f, line)) {
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
        if (line[0] == '#' || line.empty()) {
            continue;
        }
        size_t half = line.find('=');
        if (half == -1) {
            until_params = false;
            continue;
        } else if (until_params) {
            std::string name = line.substr(0, half);
            double value = std::stod(line.substr(half + 1));

            try {
                *conf_attributes[name] = value;
            }
            catch (int e) {
                throw std::invalid_argument("Invalid config argument!");
            }
        } else {
            std::string name = line.substr(0, half);
            std::string list = line.substr(half + 1);
            attributes->params[name] = split_and_double(list);
        }
    }
    return attributes;
}
