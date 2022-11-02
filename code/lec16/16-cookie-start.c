#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>

int game_running;
int jar = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv1 = PTHREAD_COND_INITIALIZER;

void* cookie_eater(void*arg) {
 char*name = (char*) arg;
  while(game_running) {
   while(jar == 0) { 
     printf("%s: \"No cookies! Going for a nap...\"\n", name);
     pthread_cond_wait( &cv1, &m);
     printf("%s has woken up!\n", name);
   }
   jar --;
   printf("%s eats! %d cookie(s) remain\n",name,jar);
   
  } //while game_running
  printf("%s finished\n",name);
  return NULL;
}

void add_cookie(int add) {
  assert( add> 0);
  jar += add;
}

int main() {
  game_running = 1;
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, cookie_eater, "Angrave");
  pthread_create(&tid2, NULL, cookie_eater, "");
  puts("Number of cookies to add to the jar? (9=exit)");
  
  int add = 0;
  while( scanf("%d", &add) == 1 && add != 9) { add_cookie(add); }

  puts("Finishing...");
  pthread_mutex_lock(&m);
  game_running = 0;
  pthread_cond_broadcast(&cv1);
  pthread_mutex_unlock(&m);
  
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  puts("Finished!");
  exit(0);
}
