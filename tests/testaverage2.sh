#/bin/sh
# no option, reading from a pipe
test "`seq 1 100 | numaverage `" = "50.500000"
