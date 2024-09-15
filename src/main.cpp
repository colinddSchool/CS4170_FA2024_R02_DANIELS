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

void parallelizer(double a, double b, int n, int numThreads, double &serialTime){
    CStopWatch timer;
    double result = 0;

    #pragma omp parallel num_threads(numThreads)

    timer.startTimer();
    result = serialTrap(square, a, b, n);
    timer.stopTimer();

    //set serial time


    if(numThreads == 1){
        serialTime = timer.getElapsedTime();
    } 
    std::cout 
    << numThreads << ", " 
    << n << ", " 
    << result << ", " 
    << timer.getElapsedTime() << ", " 
    << serialTime << ", "
    << serialTime / timer.getElapsedTime() << ", "
    << (serialTime / timer.getElapsedTime()) / numThreads
    << std::endl;
    if(numThreads == 12){
        omp_set_num_threads(1);
    } 
    else {

        omp_set_num_threads(numThreads+1);
    }
}

int main(int argc, char** argv){
 


    double pointA, pointB;


    pointA = 0;
    pointB = 16;

    int lowerN = 1000000;
    int upperN = lowerN * 10;

    double serialTime;

    std::cout << "numThreads, numTrapazoids, result, time, serialTime, speedup, efficiency" << std::endl; 
    
    for(int n = lowerN; n <= upperN; n += lowerN){
        for(int threads = 1; threads <= 12; threads++){
            parallelizer(pointA, pointB, n, threads, serialTime);
        }

    }

    
    
}







    

