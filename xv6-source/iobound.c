// I/O-bound process for testing MLFQ scheduler
// This process does I/O frequently and should stay in higher queues

#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int i;
  int pid = getpid();
  char buf[100];
  
  printf(1, "[IO-BOUND %d] Starting I/O-intensive task...\n", pid);
  
  // I/O-intensive loop
  for(i = 0; i < 50; i++){
    // Do some I/O (sleep simulates waiting for I/O)
    sleep(2);  // Sleep for 2 ticks
    
    printf(1, "[IO-BOUND %d] I/O operation %d/50 completed\n", pid, i + 1);
    
    // Small amount of CPU work
    for(int j = 0; j < 1000; j++){
      buf[j % 100] = j;
    }
  }
  
  printf(1, "[IO-BOUND %d] Completed!\n", pid);
  exit();
}
