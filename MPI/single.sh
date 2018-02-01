#!/bin/sh

qsub -q mamba -l procs=1 -d $(pwd) -v N=27950,K=20,PROC=1 ./run_heat.sh

heat_44721_20_1

qsub -q mamba -l procs=1 -l mem=9G
