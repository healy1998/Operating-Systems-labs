#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>
#include "utils.h"
int main(int argc, char* argv[])
{
   char *refStr, *tolStr;
   float refFloat, tolFloat;
   int rct, cct;
   int v = 0;
   struct tm *local;
   time_t start, end;
   time(&start);  // read and record clock
   struct timeval tim;
  
   //double t1=tim.tv_sec+(tim.tv_usec/1000000.0);
   local = localtime(&start);
   printf("# Start time and date: %s", asctime(local));
   for(int i = 0; i < argc; i++)
   {
   		if(strcmp(argv[i], "-r") == 0)
   			refFloat = strtof(argv[i+1], 0);
   			
   		if(strcmp(argv[i], "-t") == 0) 
   			tolFloat = strtof(argv[i+1], 0);
   			
   		if(strcmp(argv[i], "-v") == 0) 
   			v = 1;
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
   gettimeofday(&tim, NULL);
   double t1=tim.tv_sec+(tim.tv_usec/1000000.0);
   #pragma omp parallel for collapse(2)
   for(int i = 0; i < rct; i++)
   {
      for(int j = 0; j < cct; j++)
      {
          if(approxEqual(rows[i][j],refFloat,tolFloat))
          {
          	if(v)
          	{
          		fprintf(stdout, "r=%d, cc=%d: %.6f (thread= %d)\n",
				i, j, rows[i][j], omp_get_thread_num());
			}
			#pragma omp atomic
          	count++;
          }
      }
   }
   printf("Found %d approximate matches.\n", count);
   /*time(&end);  // read and record clock
   local = localtime(&end);
   printf("# End time and date: %s", asctime(local));*/
   gettimeofday(&tim, NULL);
   double t2=tim.tv_sec+(tim.tv_usec/1000000.0);
   printf("Search time: %.6lf(s)\n", t2-t1);
}
