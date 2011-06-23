#!/bin/sh
test `seq 1 2000 | numbound -l` = "1.000000"
