/**
* This file is part of num-utils-ng project
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 3
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program If not, see <http://www.gnu.org/licenses/>.
*
* The Original Code is Copyright (C) 2011 by num-utils-nv project.
* All rights reserved.
*
* The Original Code is: all of this file.
*
* Contributor: Edern Hotte, Flavien Moullec, Reuven Benichou and Serge Guelton.
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "utils.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include <search.h>


static const size_t default_container_size = 1024;

static double decimalPortion(double d)
{
	return d - (double)(int)d;
}

static int isHigher(const void *a, const void *b)
{
	return (*(double const *)a) - (*(double const *)b);
}


static double median(FILE * stream, bool lower)
{
	size_t nballoc = default_container_size, nbdouble = 0;
	double med, d;
	double *tab = malloc(sizeof(*tab) * nballoc);
	if (!tab) {
		perror(PACKAGE_NAME);
		exit(EXIT_FAILURE);
	}

	int test;
	while ((test = fscanf(stream, "%lf", &d)) != EOF) {
		if (!test)
			skipWord(stream);
		else {
			nbdouble++;
			if (nbdouble == nballoc) {
				nballoc *= 2;
				if (!
				    (tab =
				     realloc(tab, nballoc * sizeof(*tab)))) {
					perror(PACKAGE_NAME);
					exit(EXIT_FAILURE);
				}
			}
			tab[nbdouble - 1] = d;
		}
	}

	qsort(tab, nbdouble, sizeof(double), isHigher);
	if (decimalPortion(nbdouble / 2) == 0)
		med = tab[(nbdouble / 2) - (int)lower];
	else
		med = tab[(nbdouble - 1) / 2];
	free(tab);
	return med;
}

typedef struct {
	double val;
	size_t count;
} trecord;

static int trecord_cmp(const void *self, const void *other)
{
    return ((const trecord *)self)->val - ((const trecord *)other)->val;
}

static double tmax;
static void trecord_max(const void *nodep, const VISIT which, const int __attribute__((unused)) depth)
{
	switch (which) {
	case preorder:
		break;
	case postorder:
		break;
	case endorder:
		break;
	case leaf:{
		double d = (*(const trecord **)nodep)->val;
		if (d > tmax)
			tmax = d;
              } break;
	}
}

static double mode(FILE * stream)
{
	void *troot = NULL;
	int test;
	trecord tr = { 0., 0 };
	while ((test = fscanf(stream, "%lf", &tr.val)) != EOF) {
		if (!test)
			skipWord(stream);
		else {
			(*(trecord **) tsearch(&tr, &troot, trecord_cmp))->
			    count++;
		}
	}
	tmax = tr.val;
	twalk(troot, trecord_max);
	return tmax;;
}

static double mean(FILE * stream)
{
	double l = 0;
	double average = 0;
	double d = 0;
	int test;
	while ((test = fscanf(stream, "%lf", &d)) != EOF) {
		if (!test) {
			skipWord(stream);
		} else {
			average += d;
			l++;
		}
	}
	average /= l;
	return average;
}

int main(int argc, char *argv[])
{
	/* option default values */
	enum {
		AVERAGE,
		MEDIAN,
		MODE
	} exec_mode = AVERAGE;
	enum {
		NORMAL,
		INTEGER_PORTION,
		DECIMAL_PORTION
	} out_mode = NORMAL;	// for options (normal, integer portion and decimal portion).
	bool low = false;
	FILE *stream = stdin;	// input stream (stdin or file).

	/* parse options */
	int opt;
	while ((opt = getopt(argc, argv, "iIMmlh")) != -1) {
		switch (opt) {
		case 'i':	// option "-i" (integer portion of the average)
			out_mode = INTEGER_PORTION;
			break;

		case 'I':	//option "-I" (decimal portion of the average)
			out_mode = DECIMAL_PORTION;
			break;

		case 'M':	//option "-M" (median)
			exec_mode = MEDIAN;
			break;

		case 'l':	//option "-l" (median)
			low = true;
			break;

		case 'm':	//option "-m" (mode)
			exec_mode = MODE;
			break;

		case 'h':
			if (EOF == puts
			    ("numaverage - Find the average of a set of numbers.\n"
			     "Synopsis : numaverage [-hiIlmM] [FILE or STDIN]\n"
			     "Options available :  \n"
			     "\t-i  Only return the integer portion of the final sum\n"
			     "\t-I  Only return the decimal portion of the final sum\n"
			     "\t-m  Find the mode (most occurring) of the list of numbers\n"
			     "\t-M  Find the median (middle number) of the list of numbers\n"
			     "\t-l  When finding the median and the count of numbers in the set is even\n"
			     "\t    use the lower middle number instead of the upper middle number\n"
			     "\t-h  Help: You're looking at it.\n"
			     "You can consult the man page for further information.\n")
			    ) {
				perror(PACKAGE_NAME);
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);

		default:	//option fail.
			fputs(PACKAGE_NAME ": invalid option\n",stderr);
			exit(EXIT_FAILURE);
		}
	}
	if (argc > optind) {
		if (!(stream = fopen(argv[optind], "r"))) {
			perror(PACKAGE_NAME);
			exit(EXIT_FAILURE);
		}
	}

	double res;
	switch (exec_mode) {
	case AVERAGE:
		res = mean(stream);
		break;
	case MEDIAN:
		res = median(stream, low);
		break;
	case MODE:
		res = mode(stream);
        break;
    default:
        abort();
	}

	switch (out_mode) {
	case NORMAL:
		printf("%lf\n", res);
		break;
	case INTEGER_PORTION:
		printf("%d\n", (int)res);
		break;
	case DECIMAL_PORTION:
		printf("%lf\n", decimalPortion(res));
		break;
    default:
        abort();
	}

	if (fclose(stream) != 0) {
		perror(PACKAGE_NAME);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
	return 0;		// makes the compiler happy
}
