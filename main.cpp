#include <iostream>
#include<stdio.h>
#include<cmath>
#include<vector>

#include "conf_attributes.h"
#include "integration.h"

//#include<mpi.h>

int main(int argc, char **argv) {
    auto args = *get_intArgs("../conf.txt");

    auto res = simple_integrate(langermann_func, args, args.x1, args.x2, 0.1);
    std::cout << res << std::endl;
//    int commsize, rank, len;
//    char procname[MPI_MAX_PROCESSOR_NAME];
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Get_processor_name(procname, &len);
//
//    printf("Hello, MPI World! Process %d of %d on node %s.\n", rank, commsize, procname);
//    if (argc > 1) {
//        printf("%s\n", argv[1]);
//    }
//
//    MPI_Finalize();
    return 0;
}
