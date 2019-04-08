#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


int main(int argc, char* argv[])
{
  int flipping = (strcmp(argv[1], "-f") == 0);
  char c;
  FILE *from;
  FILE *Simon;
  if(flipping)
  {
    from = fopen(argv[2], "r");
    Simon = fopen(argv[3], "w");
  }
  else
  {
    from = fopen(argv[1], "r");
    Simon = fopen(argv[2], "w");
  }
  if (from == NULL)
  {
    perror(argv[1]);
    exit(1);
  }

  /* file exists, so start reading */
  while ((c = getc(from)) != EOF)
    if(flipping)
    {
      putc(flipChar(c),Simon);
    }
    else
    {
      putc(c,Simon);
    }
   
  fclose(from);
  fclose(Simon);

  exit(0);
 }
