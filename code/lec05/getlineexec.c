#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
   puts("What is thy command:" );
   char* lineptr = NULL;
   size_t size = 0;
   size = getline(&lineptr, &size, stdin);
   if (size > 0 && lineptr[size-1] == '\n') {
      lineptr[size-1] = '\0';
   }
   execlp(lineptr, "Name of process", "-d", (char*) NULL);
   return 0;
}
