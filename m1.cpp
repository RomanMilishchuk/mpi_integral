#include<stdio.h>
#include<cmath>
#include<vector>

#include<mpi.h>

double
langermann_func(int m, std::vector<double> a1, std::vector<double> a2, std::vector<double> c, double x1, double x2) {
    double ret = 0;
    for (int i = 1; i <= m; i++) {
        double sm = (x1 - a1[i - 1]) * (x1 - a1[i - 1]) + (x2 - a2[i - 1]) * (x2 - a2[i - 1]);
        ret -= c[i - 1] * exp(-M_1_PI * sm) * cos(M_PI * sm);
    }
    return ret;
}

int main(int argc, char** argv) {

    int commsize, rank, len ;
    char procname[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(procname, &len);

    printf ("Hello, MPI World! Process %d of %d on node %s.\n", rank, commsize, procname);
    if(argc > 1) {
        printf("%s\n", argv[1]);
    }

    MPI_Finalize();
    return 0; 
}
