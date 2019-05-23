#include <iostream>
#include<stdio.h>
#include<cmath>
#include<vector>

#include "conf_attributes.h"
#include "integration.h"

#include<mpi.h>

int main(int argc, char **argv) {
    auto args = *get_intArgs("conf.txt");
    char procname[MPI_MAX_PROCESSOR_NAME];
    int commsize, rank, len;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(procname, &len);

    double partial_res = 0, res = 0, old_res = 0;
    double step = (args.x2 - args.x1) / (commsize - 1.0);
    double dx_dy = step / 50.0;

    int is_finished = 0;
    for (int i = 0;; i++) {
        if (rank != commsize - 1) {
            partial_res = simple_integrate(langermann_func, args, args.x1 + rank * step, args.x1 + (rank + 1.0) * step,
                                           dx_dy);
        } else {
            partial_res = simple_integrate(langermann_func, args, args.x1 + rank * step, args.x2,
                                           dx_dy);
        }
        MPI_Reduce(&partial_res, &res, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        if (rank == 0) {
            if (fabs(res - old_res) < args.absolute_error &&
                (res != 0 && ((fabs(res - old_res) / res) < args.relative_error))) {
                std::cout << res << std::endl;
                is_finished = 1;
            }
            old_res = res;
        }
        dx_dy /= 1.5;
        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Bcast(&is_finished, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if (is_finished) {
            break;
        }
    }
//    printf("Hello, MPI World! Process %d of %d on node %s.\n", rank, commsize, procname);
//    printf("Result of summing %f\n", res);
//

    MPI_Finalize();
    return 0;
}
