#!/bin/bash

#SBATCH --ntasks=2
#SBATCH --time=1:00:00
#SBATCH --mail-type=END,FAIL
#SBATCH --account=PCS0288
#SBATCH --job-name=Reflection2

g++ -fopenmp ./src/main.cpp ./src/CStopWatch.cpp
./a.out > ./results.csv
