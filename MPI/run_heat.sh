#!/bin/sh

RESULTDIR=result/
h=`hostname`

if [ "$h" = "mba-i1.uncc.edu"  ];
then
    echo Do not run this on the headnode of the cluster, use qsub!
    exit 1
fi

if [ ! -d ${RESULTDIR} ];
then
    mkdir ${RESULTDIR}
fi

make 2d_heat
    
mpirun ./2d_heat ${N} ${K} 2> ${RESULTDIR}/heat_${N}_${K}_${PROC} > /dev/null

