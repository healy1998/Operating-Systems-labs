#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
int main(int argc, char* argv[])
{
   char *refStr, *tolStr;
   float refFloat, tolFloat;
   int rct, cct;
   
   struct tm *local;
   time_t start, end;
   time(&start);  // read and record clock
   local = localtime(&start);
   printf("# Start time and date: %s", asctime(local));
   if((strcmp(argv[1], "-r") == 0) && (strcmp(argv[3], "-t") == 0)) 
   {
      refFloat = strtof(argv[2], 0);
      tolFloat = strtof(argv[4], 0);
   }
   else if((strcmp(argv[1], "-t") == 0) && (strcmp(argv[3], "-r") == 0))
   {
      tolFloat = strtof(argv[2], 0);
      refFloat = strtof(argv[4], 0);
   }
   
   scanf("%d", &rct);
   scanf("%d", &cct);
   //printf("%f %f\n", refFloat, tolFloat);
   float** rows = (float **) malloc(rct * sizeof(float *));
   if(rows == 0)
   {
       fprintf(stderr, "Couldn't alocate sufficient space.\n");
       exit(1);
   }
   for(int i = 0; i < rct; i++)
   {
     float* row = (float *) malloc(cct * sizeof(float));
     if(row == 0)
     {
       fprintf(stderr, "Couldn't alocate sufficient row space. \n");
       exit(1);
     }
     rows[i] = row;
   }
   for(int i = 0; i < rct; i++)
   {
      for(int j = 0; j < cct; j++)
      {
      scanf("%f", &rows[i][j]);
      }
   }
   int count = 0;
   for(int i = 0; i < rct; i++)
   {
      for(int j = 0; j < cct; j++)
      {
          if(approxEqual(rows[i][j],refFloat,tolFloat) == 1)
          {
            fprintf(stdout, "r=%d, c=%d: %.6f\n", i, j, rows[i][j]);
            count++;
          }
      }
   }
   printf("Found %d approximate matches.\n", count);
   time(&end);  // read and record clock
   local = localtime(&end);
   printf("# End time and date: %s", asctime(local));
}
