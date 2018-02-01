#!/bin/sh

#. ./params.sh

KS="20"
NS="16000 70800 141500"

PROCS="1 4 9 16 25"

RESULTDIR=result/


if [ ! -d ${RESULTDIR} ];
then
    mkdir ${RESULTDIR}
fi

#strong scaling

for K in ${KS};
do
    for N in ${NS};
    do	

	for PROC in ${PROCS}
	do
	
	    FILE=${RESULTDIR}/matmul_${N}_${K}_${PROC}
	    
	    if [ ! -f ${FILE} ]
	    then
		MEM=$(printf "%.0f" $(echo "( ${N} * ${N} * 4 )" | bc -l ))
		qsub -q mamba -l procs=${PROC} -l mem=${MEM} -d $(pwd) -v N=${N},K=${K},PROC=${PROC} ./run_matmul.sh
	    fi

	done

    done
done


#weak scaling
NS="1000 2000 4000"

for K in ${KS};
do
    for N in ${NS};
    do	

	for PROC in ${PROCS}
	do
	    
	    REALN=$(printf "%.0f" $(echo "sqrt (250000 * ${PROC} * ${N} )" | bc -l))
	    
	    FILE=${RESULTDIR}/matmul_${REALN}_${K}_${PROC}
	    
	    if [ ! -f ${FILE} ]
	    then
		MEM=$(printf "%.0f" $(echo "( ${REALN} * ${REALN} * 4 )" | bc -l ))
		qsub -q mamba -l procs=${PROC} -l mem=${MEM} -d $(pwd) -v N=${REALN},K=${K},PROC=${PROC} ./run_matmul.sh
	    fi

	done

    done
done


