// CPU-bound process for testing MLFQ scheduler
// This process uses CPU intensively and should be demoted to lower queues

#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int i, j;
  int pid = getpid();
  
  printf(1, "[CPU-BOUND %d] Starting CPU-intensive task...\n", pid);
  
  // CPU-intensive loop
  for(i = 0; i < 100; i++){
    // Busy work
    for(j = 0; j < 1000000; j++){
      asm("nop");  // No operation - just burn CPU
    }
    
    if(i % 10 == 0){
      printf(1, "[CPU-BOUND %d] Iteration %d/100\n", pid, i);
    }
  }
  
  printf(1, "[CPU-BOUND %d] Completed!\n", pid);
  exit();
}
