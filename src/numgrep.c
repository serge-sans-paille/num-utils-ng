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
* Contributor(s): Edern Hotte, Flavien Moullec, Reuven Benichou.
*
* ***** END GPL LICENSE BLOCK *****
*/



#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


enum
{ ERROR_1 = 1, WRONG_ARG, ERROR_3, WRONG_FILE, OPTION_ERROR };


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
  return EXIT_SUCCESS;
}


static int
numgrep (FILE * stream, char expression[])
{
  int numberRead, number1, number2;
  int j;
  size_t i, count = 0;
  char *token;
  char *savestr = NULL;
  char *str;
  char **tab = NULL;
  int test;

  for (i = 0; i < strlen (expression); i++)
    {
      switch (expression[i])
	{
	case '/':
	  expression[i] = ',';
	  break;
	case '.':
	  break;
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
	  break;
	case '-':
	  break;
	case 'f':
	  break;
	case 'm':
	  break;
	case ',':
	  count++;
	  break;
	default:
	  return EXIT_SUCCESS;
	}
    }
  if (!(tab = (char **) calloc (count + 1, sizeof (char *))))
    {
      perror ("num-utils-ng");
      return EXIT_FAILURE;
    }
  for (i = 0, str = expression;; i++, str = NULL)
    {
      token = strtok_r (str, ",", &savestr);
      if (token == NULL)
	break;
      *(tab + i) = token;
    }

  while ((test = fscanf (stream, "%d", &numberRead)) != EOF)
    {
      if (!test)
	skipWord (stream);
      for (i = 0; i <= count; i++)
	{

	  if (strstr (*(tab + i), "f") != NULL)
	    {
	      sscanf (*(tab + i), "f%d", &number1);
	      if ((number1 >= numberRead) && (number1 % numberRead == 0))
		printf ("%d\n", numberRead);
	    }

	  else if (strstr (*(tab + i), "m") != NULL)
	    {
	      sscanf (*(tab + i), "m%d", &number1);
	      if ((numberRead >= number1) && (numberRead % number1 == 0))
		printf ("%d\n", numberRead);
	    }

	  else if (strstr (*(tab + i), "..") != NULL)
	    {
	      sscanf (*(tab + i), "%d..%d", &number1, &number2);
	      if (number1 < number2)
		{
		  for (j = number1; j <= number2; j++)
		    {
		      if (numberRead == j)
			printf ("%d\n", numberRead);
		    }
		}
	    }

	  else
	    {
	      sscanf (*(tab + i), "%d", &number1);
	      if (numberRead == number1)
		printf ("%d\n", numberRead);
	    }
	}
    }
  free (tab);
  return EXIT_SUCCESS;
}


int
main (int argc, char *argv[])
{
  FILE *stream = stdin;
  char *arg = NULL;
  int optch;

  while ((optch = getopt (argc, argv, "h")) != -1)
    {
      switch (optch)
	{

	case 'h':
	  fprintf(stdout,"numgrep - This program is the numeric equivalent of the grep utility.\nSynopsis : numgrep [-h] /<expression>/\nOptions available :  \n\t/<expression>/  Put your expression or set of expressions between these two forward slashes.\n\t..  Range expression. A number must be used on the left and/or right of this  expression  to specify that numbers between, greater than or less than the numbers specified should be matched.\n\t, Expression separator. The comma sepearates  one  complete  expression from another in a set enclosed by //.\n\tm<n>  Multiples  of  <n>.  This operator, followed by a number <n> will match any number <x> that is an integer multiple of <n>.  Meaning  that <x> = <n> times <y>, where <y> is any integer.\n\tf<n>  Factors  of  <n>.   This  operator, followed by a number <n> will match any number <x> that is an integer factor of  <n>.   Meaning  that <x> = <n> divided by <y>, where <y> is any integer.\n\t-h  Help: You're looking at it.\nYou can consult the man page for further information.\n");
	  return EXIT_SUCCESS;
	  break;

	default:		//option fail.
	  perror ("invalid option\n");
	  return OPTION_ERROR;
	  break;
	}
    }


  if (argv[optind][0] == '/') {
  arg = argv[optind];
  }
  if (!arg)
    {
      perror ("num-utils-ng");
      return WRONG_ARG;
    }
  if (argc > optind + 1)
    {
      if (!(stream = fopen (argv[optind + 1], "r")))
	{
	  perror ("num-utils-ng");
	  return WRONG_FILE;
	}
    }
  numgrep (stream, arg);
  fclose (stream);
  return EXIT_SUCCESS;
}
