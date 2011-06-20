#!/bin/sh
# using average option, negative values from a pipe, with integral part
test "`seq -100 101 | numaverage -i`" = 0
