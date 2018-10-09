#ifdef _OPENMP
    #include <omp.h>
#endif
#include <iostream>

int main(){

    #ifdef _OPENMP
        int myRank = omp_get_thread_num();
        int numThreads = omp_get_num_threads();
    #else
        int myRank = 0;
        int numThreads = 1;
    #endif


    return 0;
}