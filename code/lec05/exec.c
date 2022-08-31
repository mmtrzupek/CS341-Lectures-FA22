#include <unistd.h>
#include <stdio.h>

int main(int argc, char**argv) {
   printf("Executing %s ...\n", *(argv+1)); // can also use argv[1] to start at the 2nd entry in the array
   execvp( argv + 1, argv + 1);
   perror("Failed to be all powerful");
}
