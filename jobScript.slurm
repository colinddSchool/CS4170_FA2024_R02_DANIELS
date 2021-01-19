#!/bin/bash

#SBATCH --nodes=1 
#SBATCH --ntasks-per-node=12
#SBATCH -time=1:00:00
#SBATCH --mail-type=END,FAIL
#PBS -j oe
#SBATCH --account=PCS0253
#SBATCH --job-name=JOB_NAME

export OMP_NUM_THREADS=12
cd $SLURM_SUBMIT_DIR/Default
./OpenMP > $PBS_O_WORKDIR/results.csv