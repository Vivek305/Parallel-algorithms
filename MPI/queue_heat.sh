#!/bin/sh

#. ./params.sh

KS="20"
NS="16000 50000 111800"

PROCS="1 2 4 8 16 32"

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
	
	    FILE=${RESULTDIR}/static_${N}_${K}_${PROC}
	    
	    if [ ! -f ${FILE} ]
	    then
		MEM=$(printf "%.0f" $(echo "( ${N} * ${N} * 8 )" | bc -l ))
		qsub -q mamba -l procs=${PROC} -l mem=${MEM} -d $(pwd) -v N=${N},K=${K},PROC=${PROC} ./run_heat.sh
	    fi

	done

    done
done


#weak scaling
NS="500 1000 2000"

for K in ${KS};
do
    for N in ${NS};
    do	

	for PROC in ${PROCS}
	do
	    
	    REALN=$(printf "%.0f" $(echo "sqrt (250000 * ${PROC} * ${N} )" | bc -l))
	    
	    FILE=${RESULTDIR}/static_${REALN}_${K}_${PROC}
	    
	    if [ ! -f ${FILE} ]
	    then
		MEM=$(printf "%.0f" $( echo "( ${REALN} * ${REALN} * 8 )" | bc -l ))
		qsub -q mamba -l procs=${PROC} -l mem=${MEM} -d $(pwd) -v N=${REALN},K=${K},PROC=${PROC} ./run_heat.sh
	    fi

	done

    done
done



