AM_CPPFLAGS=-Wall -Wextra -Werror
AM_LDFLAGS=-lm

bin_PROGRAMS = numaverage numbound numinterval numnormalize numgrep numprocess numsum numrandom numround numrange

numaverage_LDFLAGS = $(AM_LDFLAGS)
numaverage_SOURCES = numaverage.c utils.c
numbound_SOURCES = numbound.c utils.c
numinterval_SOURCES = numinterval.c utils.c
numnormalize_SOURCES = numnormalize.c utils.c
numgrep_SOURCES = numgrep.c utils.c
numprocess_SOURCES = numprocess.c utils.c
numsum_SOURCES = numsum.c utils.c
numrandom_SOURCES = numrandom.c utils.c
numround_SOURCES = numround.c utils.c
numrange_SOURCES = numrange.c utils.c

dist_noinst_HEADERS=utils.h
