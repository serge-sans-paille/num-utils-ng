#!/bin/sh
# using median option, from a pipe
test "`seq 1 100 | numaverage -M`" = 51.000000
