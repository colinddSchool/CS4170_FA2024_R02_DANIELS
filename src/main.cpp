#include <omp.h>
#include <iostream>
#include "CStopWatch.h"


double triple(double x){
    return x * 3;
}
double square(double x){
    return x * x;
}

void getHeight(double(*function)(double n), double x){
    std::cout << "height: " << function(x) << std::endl;
}

double serialTrap(double(*f)(double n), double a, double b, int n){
    double retValue, trapWidth, x;

    trapWidth = (b - a) / n;
    retValue = (f(a) + f(b)) / 2.0;

    #pragma omp parallel for reduction(+:retValue)
    for(int i = 1; i < n; i++){
        x = a + i * trapWidth;
        retValue += f(x);
    }

    retValue *= trapWidth;
    return retValue;

}

void parallelizer(double a, double b, int n, int numThreads){
    CStopWatch timer;
    double result = 0;

    #pragma omp parallel num_threads(numThreads)
    timer.startTimer();
    result = serialTrap(square, a, b, n);
    timer.stopTimer();

    std::cout << numThreads << ", " << n << ", " << result << ", " << timer.getElapsedTime() << std::endl;


   
}

int main(int argc, char** argv){
 


    double pointA, pointB;


    pointA = 0;
    pointB = 16;

    std::cout << "numThreads, numTrapazoids, result, time" << std::endl; 
    
    for(int threads = 1; threads <= 12; threads++){
        for(int n = 10000; n <=100000; n += 10000){
            parallelizer(pointA, pointB, n, threads);
        }

    }

    
    
}







    

