#include <omp.h>
#include <random>
#include <iostream>

double f(double x) {
    return x * x; // Example function: f(x) = x^2
}

double serialTrap(double a, double b, int n) {

    double h, retValue, x;

    h = (b - a) / n;
    retValue = (f(a) + f(b)) / 2.0;

    for (int i = 1; i < n; i++) {
        x = a + i * h;
        retValue += f(x);
    }

    retValue *= h;
    return retValue;
}

void parallelTrap(double a, double b, int n, double &result){

    double h, x, myRetValue;
    int myId = omp_get_thread_num();
    int numThreads = omp_get_num_threads();

    int myN, myA, myB;

    h = (b - a) / n;
    
    myN = n/numThreads;
    myA = a + myId * myN * h;
    myB = myA + myN * h;
    myRetValue  = (f(myA) + f(myB)) / 2.0;

    for (int i = 1; i < myN; i++) {
        x = myA + i * h;
        myRetValue += f(x);
    }
    myRetValue *= h;

    #pragma omp critical
    {
        result += myRetValue;
    }
}

int main(){

    double result = 0;
    double a, b;
    int n;

    a = 2;
    b = 14;
    n = 76;

    result = serialTrap(a, b, n);
    std::cout << "Serial Result: " << result << std::endl;

    omp_set_num_threads(4);
    result = 0.0;
    #pragma omp parallel
    parallelTrap(a, b, n, result);
    std::cout << "Parallel Result: " << result << std::endl;

    return 0;
}


