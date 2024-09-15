#!/bin/bash

#SBATCH --ntasks=1
#SBATCH --time=1:00:00
#SBATCH --mail-type=END,FAIL
#SBATCH --account=PCS0253
#SBATCH --job-name=Reflection 2

g++ -fopenmp ./src/main.cpp ./src/CStopWatch.cpp
./a.out > ./results.csv
