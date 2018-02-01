#!/bin/sh

make approx

#./reduce <n> <nbthreads>
for n in 10 1000;
do
    for nbthreads in 1 3;
    do
	#for scheduling in static dynamic guided;
	#do
	    #for gran in 1 100 -1;
	    #do
	    #TEST1=$(./reduce $n $nbthreads $scheduling $gran 2> /dev/null)
		TEST1=$(./reduce $n $nbthreads 2> /dev/null)
		if ./approx 0 "$TEST1";
		then
		    echo oktest "./reduce $n $nbthreads"
		else
		    echo notok "./reduce $n $nbthreads" 
		    exit 1
		fi
	    #done
	#done
    done
done
