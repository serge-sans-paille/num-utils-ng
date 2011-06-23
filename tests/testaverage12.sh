#!/bin/sh
# using average option, negative values from a pipe, with decimal part
cat > data << EOF
1
2
3
4
2
EOF
if test 2.000000 = "`numaverage -m data`" ; then
	rm -f data
else
	exit 1
fi
