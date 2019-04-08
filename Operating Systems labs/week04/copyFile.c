#include <stdio.h>
#include <stdlib.h>

int main()
{
  char c;
  FILE *from;
  FILE *Simon;

  from = fopen("file.txt", "r");
  Simon = fopen("copy.txt", "w");
  if (from == NULL)
  {
    perror("file.txt");
    exit(1);
  }

  /* file exists, so start reading */
  while ((c = getc(from)) != EOF)
    putc(c, Simon);

  fclose(from);
  fclose(Simon);

  exit(0);
}
