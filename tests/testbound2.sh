#!/bin/sh
seq -1 2000 > data
if test "`numbound data -l`" = "-1.000000"
then
	rm -f data
else
	exit 1
fi
