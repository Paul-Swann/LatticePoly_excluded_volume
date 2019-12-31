#!/bin/bash -l

if [ "$#" -ge "3" ]; then
	find $2 -mindepth 1 -maxdepth 1 -type d -exec python3 $1 {} ${@: 3} \;
else
	echo "\033[1;31mUsage is $0 scriptName rootDataDir initFrame [opt]\033[0m"
fi
