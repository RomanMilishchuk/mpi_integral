#include "integration.h"

double
langermann_func(int m, std::vector<double> a1, std::vector<double> a2, std::vector<double> c, double x1, double x2) {
    double ret = 0;
    for (int i = 1; i <= m; i++) {
        double sm = (x1 - a1[i - 1]) * (x1 - a1[i - 1]) + (x2 - a2[i - 1]) * (x2 - a2[i - 1]);
        ret -= c[i - 1] * exp(-M_1_PI * sm) * cos(M_PI * sm);
    }
    return ret;
}

void simple_integrate(double (*func)(int, std::vector<double>, std::vector<double>, std::vector<double>, double,
                                     double), IntegralAttributes &args, double x1, double x2, double dx_dy,
                      double &res) {
    double cur_res = 0;
    for (double x = x1; x < x2; x += dx_dy) {
        for (double y = args.y1; y < args.y2; y += dx_dy) {
            cur_res +=
                    func(static_cast<int>(args.params["m"][0]), args.params["a1"], args.params["a2"], args.params["c"],
                         x, y) *
                    dx_dy * dx_dy;
        }
    }
    res = cur_res;
}

