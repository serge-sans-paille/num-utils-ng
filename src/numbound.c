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
* Contributor(s): Edern Hotte, Flavien Moullec, Reuven Benichou and Serge Guelton.
*
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "utils.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <values.h>

static double bound(FILE * stream, bool upper_bound_p)
{
	double lowerBound = DBL_MAX;
	double upperBound = DBL_MIN;
	double number = 0.;
	int test;
	while ((test = fscanf(stream, "%lf", &number)) != EOF) {
		if (!test)
			skipWord(stream);
		if (number > upperBound)
			upperBound = number;
		if (number < lowerBound)
			lowerBound = number;
	}
	return upper_bound_p ? upperBound : lowerBound;
}

int main(int argc, char *argv[])
{
	FILE *stream = stdin;
	enum {
		UPPER_BOUND,
		LOWER_BOUND
	} exec_mode = UPPER_BOUND;

	int optch;
	while ((optch = getopt(argc, argv, "lh")) != -1) {
		switch (optch) {
		case 'l':	//option "-l" (the lower bound number)
			exec_mode = LOWER_BOUND;
			break;

		case 'h':
			if (EOF ==
			    puts
			    ("numbound - Find boundary numbers in files or STDIN.\n"
			     "Synopsis : numbound [-hl] [FILE or STDIN]\n"
			     "Options available :  \n"
			     "\t-l  Return the lower bound number in the set (the minimum number).\n"
			     "\t-h  Help: You're looking at it.\n"
			     "You can consult the man page for further information.\n")
			    ) {
				perror(PACKAGE_NAME);
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);

		default:	//option fail.
			fputs(PACKAGE_NAME ": invalid option\n", stderr);
			exit(EXIT_FAILURE);
		}
	}
	if (argc > optind) {
		if (!(stream = fopen(argv[optind], "r"))) {
			perror(PACKAGE_NAME);
			exit(EXIT_FAILURE);
		}
	}

	double res = bound(stream, exec_mode == UPPER_BOUND);

	printf("%lf\n", res);
	if (fclose(stream)) {
		perror(PACKAGE_NAME);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
	return 0;		// makes the compiler happy
}
