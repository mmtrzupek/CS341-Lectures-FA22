#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

ssize_t mygetline(char **lineptr, size_t *n, FILE *f){
  assert(lineptr);
  assert(f);
  assert(n);

  if(*n == 0 || *lineptr)  { *n = 256; *lineptr = malloc(*n);}
  size_t bytesread = 0;
  int c = 0;
  while( ferror(f)==0 && feof(f)==0 ){
      if (bytesread == *n) { /* extend buffer */ 
        void* myoldstuff = *lineptr;
        size_t old_capacity = *n;
        *n *= 2;
        *lineptr = malloc(*n);
        memcpy(*lineptr, myoldstuff, old_capacity);
      }
      c = fgetc(f);
      (*lineptr)[bytesread] = c;
      if (c == '\n') ...
  }
   return -1; // error (e.g. end of file)
}

