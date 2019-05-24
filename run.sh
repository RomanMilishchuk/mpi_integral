mpic++ main.cpp conf_attributes.cpp integration.cpp -o prog -std=c++11
mpirun -n 8 ./prog
