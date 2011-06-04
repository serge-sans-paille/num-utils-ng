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
#include <string.h>
#include <math.h>
#include <ctype.h>

enum
{
  TYPE_ERROR = 1,
  OPTION_ERROR,
  MISSEXPR_ERROR,
  EXPR_ERROR,
};

static double
calculate (double res, char *expression)
{
  size_t i;
  double p = 0;
  for (i = 0; i < strlen (expression); i++)
    {
      switch (expression[i])
	{
	case '/':
	case ',':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'e':
	  break;
	case '*':
	  if (isdigit (expression[i + 1]))
	    p = atoi (expression + i + 1);
	  if (expression[i + 1] == 'e')
	    {
	      p = M_E;
	      i++;
	    }
	  if ((expression[i + 1] == 'p') && (expression[i + 2] == 'i'))
	    {
	      p = M_PI;
	      i = i + 2;
	    }
	  res = res * p;
	  break;
	case '%':
	  if (isdigit (expression[i + 1]))
	    p = atoi (expression + i + 1);
	  if (expression[i + 1] == 'e')
	    {
	      p = M_E;
	      i++;
	    }
	  if ((expression[i + 1] == 'p') && (expression[i + 2] == 'i'))
	    {
	      p = M_PI;
	      i = i + 2;
	    }
	  res = res / p;
	  break;
	case '+':
	  if (isdigit (expression[i + 1]))
	    p = atoi (expression + i + 1);
	  if (expression[i + 1] == 'e')
	    {
	      p = M_E;
	      i++;
	    }
	  if ((expression[i + 1] == 'p') && (expression[i + 2] == 'i'))
	    {
	      p = M_PI;
	      i = i + 2;
	    }
	  res = res + p;
	  break;
	case '-':
	  if (isdigit (expression[i + 1]))
	    p = atoi (expression + i + 1);
	  if (expression[i + 1] == 'e')
	    {
	      p = M_E;
	      i++;
	    }
	  if ((expression[i + 1] == 'p') && (expression[i + 2] == 'i'))
	    {
	      p = M_PI;
	      i = i + 2;
	    }
	  res = res - p;
	  break;
	case '^':
	  p = (double) atoi (expression + i + 1);
	  res = powl (res, p);
	  break;
	case 's':
	  if ((expression[i + 1] == 'i') && (expression[i + 2] == 'n'))
	    {
	      res = sin (res);
	      i = i + 2;
	    }
	  if ((expression[i + 1] == 'q') && (expression[i + 2] == 'r')
	      && (expression[i + 3] == 't'))
	    {
	      res = sqrt (abs (res));
	      i = i + 3;
	    }
	  break;
	case 'c':
	  if ((expression[i + 1] == 'o') && (expression[i + 2] == 's'))
	    {
	      res = cos (res);
	      i = i + 2;
	    }
	  break;
	default:
	  return EXIT_FAILURE;
	  break;
	}
    }
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
stdinprocess (char *expression)
{
  double res;
  int test;
  while ((test = fscanf (stdin, "%lf", &res)) != EOF)
    {
      if (test == 0)
	skipWord (stdin);
      else
	{
	  fprintf (stdout, "%lf\n", calculate (res, expression));
	}
    }
  return 1;
}

static int
fileprocess (FILE * stream, char *expression)
{
  double res = 0;
  int end = 0;
  char c;
  FILE *streamout = NULL;
  streamout = fopen ("./tempprocess", "w");
  while ((fscanf (stream, "%c", &c) != EOF) && end != 1)
    {
      while (!isdigit (c) && !(c == 46) && !(c == 45))
	{
	  fprintf (streamout, "%c", c);
	  if (fscanf (stream, "%c", &c) == EOF)
	    {
	      end = 1;
	      c = '1';
	    }
	}

      fseek (stream, -1 * sizeof (char), SEEK_CUR);

      if (fscanf (stream, "%lf", &res) == EOF)
	{
	  end = 1;
	  c = '1';
	}

      if (end != 1)
	{
	  fprintf (streamout, "%lf", calculate (res, expression));
	}
    }
  fclose (streamout);
  return 1;
}


int
main (int argc, char *argv[])
{
  FILE *stream = NULL;
  int opt;

  while ((opt = getopt (argc, argv, "iIMmlh")) != -1)
    {
      switch (opt)
	{
	case 'h':
	  fprintf(stdout,"numprocess - This program mutates numbers as it encounters them.\nSynopsis : numprocess [-h] /<expression>/ [FILE or STDIN]\nThe expression has to take this form : /+1,%%2,*pi/\nThe possibilities for the operatos are : +,-,*,%%,sin,cos,sqrt and ^\nYou can also use the constants pi and e.\nThe only option is the help (-h) option and you are looking at it.\nReturn values : \n\t 1 : Option error \n\t 2 : Missing expression \n\t 3 : Wrong expression.\nNote 1 : If you are using numprocess on files, everything that is not a number will be ignored (Only the number will be processed), but if you use stdin as an input the words will be deleted.\nNote 2 : Don't begin an expression with the operation \"*e\", it will search for a file in the root directory.\nYou can consult the man page for further information.\n");
	  return 0;
	  break;

	default:		//option fail.
	  fprintf (stderr, "Invalid option\n");
	  return OPTION_ERROR;
	  break;
	}
    }
  if (argc == 1)
    {
      fprintf (stderr, "The expression is missing.\n");
      return MISSEXPR_ERROR;
    }
  if (argv[1][0] != '/')
    {
      fprintf (stderr, "The expression is wrong.\n");
      return EXPR_ERROR;
    }
  if (argc == (optind + 1))
    stdinprocess (argv[optind]);
  else
    {
      if (!(stream = fopen (argv[optind + 1], "r")))
	{
	  perror ("num-utils-ng");
	  return EXIT_FAILURE;
	}
      fileprocess (stream, argv[optind]);
      fclose (stream);
      remove (argv[optind + 1]);
      rename ("./tempprocess", argv[optind + 1]);
    }
  return 0;
}
