#!/bin/bash
echo "Left in queue: "  $(qstat | grep kkluttz | grep Q | wc -l)
echo "Blank results: " $(ls -l result/ | grep "z5 0" | wc -l)
echo "Total queue: " $(qstat | grep Q | wc -l)

ls -l result/ | grep "z5 0"
