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
	FILE=${RESULTDIR}/heat_${N}_${K}_1
	if [ ! -f ${FILE} ]
	then
	    echo missing sequential result file "${FILE}". Have you run queue_sequential and waited for completion?
	fi

	seqtime=$(cat ${RESULTDIR}/heat_${N}_${K}_1)
	
	for PROC in ${PROCS}
	do
	
	    FILE=${RESULTDIR}/heat_${N}_${K}_${PROC}
	    
	    if [ ! -f ${FILE} ]
	    then
		echo missing static result file "${FILE}". Have you run queue_static and waited for completion?
	    fi

	    partime=$(cat ${RESULTDIR}/heat_${N}_${K}_${PROC})
	    
	    echo ${PROC} ${seqtime} ${partime}
	done > ${RESULTDIR}/speedup_heat_ni_${N}_${K}


	GNUPLOTSTRONG="$GNUPLOTSTRONG set title 'strong scaling. n=${N} k=${K}'; plot '${RESULTDIR}/speedup_heat_ni_${N}_${K}' u 1:(\$2/\$3);"
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
	    
	    FILE=${RESULTDIR}/heat_${REALN}_${K}_${PROC}
	    
	    if [ ! -f ${FILE} ]
	    then
		echo missing static result file "${FILE}". Have you run queue_static and waited for completion?
	    fi

	    partime=$(cat ${RESULTDIR}/heat_${REALN}_${K}_${PROC})
	    
	    echo ${PROC} ${partime}
	done > ${RESULTDIR}/time_heat_ni_${N}_${K}


	GNUPLOTWEAK="$GNUPLOTWEAK set title 'weak scaling. n=${N}MB k=${K}'; plot '${RESULTDIR}/time_heat_ni_${N}_${K}' u 1:2;"
    done
done


gnuplot <<EOF
set terminal pdf
set output '2d_heat_plots.pdf'

set style data linespoints

set key top left

set xlabel 'Proc'
set ylabel 'Speedup'

${GNUPLOTSTRONG}

set xlabel 'Proc'
set ylabel 'Time (in s)'

${GNUPLOTWEAK}


EOF
