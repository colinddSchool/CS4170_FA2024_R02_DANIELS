#include <omp.h>
#include <random>
#include <iostream>
#include "CStopWatch.h"

double f(double x) {
    return x * x; // Example function: f(x) = x^2
}

double serialTrap(double a, double b, int n) {

    double h, retValue, x;

    h = (b - a) / n;
    retValue = (f(a) + f(b)) / 2.0;

    #pragma omp parallel for reduction(+:retValue)
    for (int i = 1; i < n; i++) {
        x = a + i * h;
        retValue += f(x);
    }

    retValue *= h;
    return retValue;
}

int main(){

    double result = 0;
    double a, b;
    int n;
    CStopWatch timer;

    a = 2;
    b = 14;
    n = 40000;

    #pragma omp parallel num_threads(1)

    timer.startTimer();
    result = serialTrap(a, b, n);
    timer.stopTimer();
    std::cout << "Serial Result: " << result << std::endl;
    std::cout << "Serial Time:" << timer.getElapsedTime() << std::endl;

    omp_set_num_threads(4);
    result = 0.0;
    
    #pragma omp parallel num_threads(4)
    timer.startTimer();
    result = serialTrap(a, b, n);
    timer.stopTimer();
    std::cout << "Parallel Result: " << result << std::endl;
    std::cout << "Parallel Time:" << timer.getElapsedTime() << std::endl;

    return 0;
}


