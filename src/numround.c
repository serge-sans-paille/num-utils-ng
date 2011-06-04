/**
*
*
* ***** BEGIN GPL LICENSE BLOCK *****
*
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
* Contributor: Edern Hotte, Flavien Moullec, Reuven Benichou.
*
* ***** END GPL LICENSE BLOCK *****
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>

static double
decimalPortion (double d)
{
  int i = (int) d;
  double res = d - (double) i;
  return res;
}

static int
skipWord (FILE * stream)
{
  char c = 'a';
  if (stream == stdin)
    fprintf (stderr, "This is not a number!\n");
  while (!isdigit (c) && !isspace (c) && !(c == 46) && !(c == 45))
    {
      if (fscanf (stream, "%c", &c) != 1)
	{
	  perror ("num-utils-ng");
	  return EXIT_FAILURE;
	}
    }
  return 0;
}

static int
roundc (FILE * stream, int c, int f, int n)
{
  double d;
  int test;
  while ((test = fscanf (stream, "%lf", &d)) != EOF)
    {
      if (test == 0)
	skipWord (stream);
      else
	{
	  d = d / (double) n;
	  if (decimalPortion (d) == 0)
	    printf ("result : %d\n", (int) d * n);
	  else if (fabs (decimalPortion (d)) < 0.5)
	    {
	      if (d >= 0)
		printf ("result : %d\n", (int) (d + c) * n);
	      else
		printf ("result : %d\n", (int) (d - f) * n);
	    }
	  else
	    {
	      if (d >= 0)
		printf ("result : %d\n", (int) (d + 1 - f) * n);
	      else
		printf ("result : %d\n", (int) (d - 1 + c) * n);
	    }
	}
    }
  return 0;
}

int
main (int argc, char *argv[])
{
  int opt = 0, c = 0, f = 0, n = 1;
  FILE *stream = stdin;
  while ((opt = getopt (argc, argv, "hcfn:")) != -1)
    {
      switch (opt)
	{

	case 'h':
	  fprintf(stdout,"numround - A program that rounds off numbers it encounter.\nSynopsis : numround [-hcfn] <FILE> or STDIN\nOptions available :  \n\t-c Force the number to be rounded up. Ceiling.\n\t-f  Force the number to be rounded down. Floor.\n\t-n <n>  Round numbers to the nearest factor of <n>.\n\t-h  Help: You're looking at it.\nYou can consult the man page for further information.\n");
	  return 0;
	  break;

	case 'c':
	  c = 1;
	  break;

	case 'f':
	  f = 1;
	  break;

	case 'n':
	  n = atoi (optarg);
	  break;

	default:		//option fail.
	  fprintf (stderr, "invalid option \n");
	  return EXIT_FAILURE;
	  break;
	}
    }

  if (argc > optind)
    {
      if (!(stream = fopen (argv[optind], "r")))
	{
	  perror ("num-utils-ng");
	  return EXIT_FAILURE;
	}
    }
  roundc (stream, c, f, n);
  if (argc > optind)
    {
      if (fclose (stream) != 0)
	{
	  perror ("num-utils-ng");
	  return EXIT_FAILURE;
	}
    }

  return 0;
}
