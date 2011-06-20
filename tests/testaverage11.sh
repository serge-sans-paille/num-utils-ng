#!/bin/sh
# using average option, negative values from a pipe, with decimal part
test "`seq -100 101 | numaverage -I`" = 0.500000
