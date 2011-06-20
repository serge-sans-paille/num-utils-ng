#!/bin/sh
# using median option, from a pipe, with lower bound
test "`seq 1 100 | numaverage -M -l`" = 50.000000
