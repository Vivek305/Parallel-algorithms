#!/bin/sh

#qsub -q mamba -l procs=1 -l mem=4G -d $(pwd) -v N=27950,K=20,PROC=1 ./run_heat.sh


#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 00:55 heat_111800_20_16
#qsub -q mamba -l procs=16 -l mem=101G -d $(pwd) -v N=111800,K=20,PROC=16 ./run_heat.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 00:15 heat_111800_20_2
qsub -q mamba -l procs=2 -l mem=101G -d $(pwd) -v N=111800,K=20,PROC=2 ./run_heat.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 04:32 heat_111800_20_32
#qsub -q mamba -l procs=32 -l mem=4G -d $(pwd) -v N=111800,K=20,PROC=32 ./run_heat.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 00:14 heat_111800_20_4
qsub -q mamba -l procs=4 -l mem=101G -d $(pwd) -v N=111800,K=20,PROC=4 ./run_heat.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 00:27 heat_111800_20_8
qsub -q mamba -l procs=4 -l mem=101G -d $(pwd) -v N=111800,K=20,PROC=8 ./run_heat.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 04:40 heat_126491_20_32
qsub -q mamba -l procs=32 -l mem=129G -d $(pwd) -v N=126491,K=20,PROC=32 ./run_heat.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 00:11 heat_16000_20_4
#qsub -q mamba -l procs=4 -l mem=1G -d $(pwd) -v N=16000,K=20,PROC=4 ./run_heat.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 00:11 heat_31623_20_4
#qsub -q mamba -l procs=4 -l mem=2G -d $(pwd) -v N=31623,K=20,PROC=4 ./run_heat.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 04:31 heat_50000_20_32
#qsub -q mamba -l procs=32 -l mem=1G -d $(pwd) -v N=50000,K=20,PROC=32 ./run_heat.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 04:34 heat_63246_20_32
#qsub -q mamba -l procs=32 -l mem=2G -d $(pwd) -v N=63246,K=20,PROC=32 ./run_heat.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 00:28 heat_63246_20_8
#qsub -q mamba -l procs=8 -l mem=5G -d $(pwd) -v N=63246,K=20,PROC=8 ./run_heat.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 00:56 heat_89443_20_16
#qsub -q mamba -l procs=16 -l mem=5G -d $(pwd) -v N=89443,K=20,PROC=16 ./run_heat.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 04:36 heat_89443_20_32
#qsub -q mamba -l procs=32 -l mem=3G -d $(pwd) -v N=89443,K=20,PROC=32 ./run_heat.sh



#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 15:05 result/matmul_111803_20_25
#qsub -q mamba -l procs=25 -l mem=3G -d $(pwd) -v N=111803,K=20,PROC=25 ./run_matmul.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 14:31 result/matmul_126491_20_16
#qsub -q mamba -l procs=16 -l mem=5G -d $(pwd) -v N=126491,K=20,PROC=16 ./run_matmul.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 14:30 result/matmul_141500_20_16
#qsub -q mamba -l procs=16 -l mem=6G -d $(pwd) -v N=141500,K=20,PROC=16 ./run_matmul.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 15:06 result/matmul_141500_20_25
#qsub -q mamba -l procs=25 -l mem=5G -d $(pwd) -v N=141500,K=20,PROC=25 ./run_matmul.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 12:54 result/matmul_141500_20_4
#qsub -q mamba -l procs=4 -l mem=82G -d $(pwd) -v N=141500,K=20,PROC=4 ./run_matmul.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 12:56 result/matmul_141500_20_9
#qsub -q mamba -l procs=9 -l mem=11G -d $(pwd) -v N=141500,K=20,PROC=9 ./run_matmul.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 15:05 result/matmul_158114_20_25
#qsub -q mamba -l procs=25 -l mem=5G -d $(pwd) -v N=158114,K=20,PROC=25 ./run_matmul.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 12:54 result/matmul_70800_20_4
#qsub -q mamba -l procs=4 -l mem=6G -d $(pwd) -v N=70800,K=20,PROC=4 ./run_matmul.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 14:30 result/matmul_89443_20_16
#qsub -q mamba -l procs=16 -l mem=3G -d $(pwd) -v N=89443,K=20,PROC=16 ./run_matmul.sh
#-rw------- 1 kkluttz5 kkluttz5 0 Dec  8 12:58 result/matmul_94868_20_9
#qsub -q mamba -l procs=9 -l mem=5G -d $(pwd) -v N=94868,K=20,PROC=9 ./run_matmul.sh




