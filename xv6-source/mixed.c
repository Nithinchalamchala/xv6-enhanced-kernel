// Mixed workload process for testing MLFQ scheduler
// Alternates between CPU and I/O work

#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int i, j;
  int pid = getpid();
  
  printf(1, "[MIXED %d] Starting mixed workload...\n", pid);
  
  for(i = 0; i < 20; i++){
    // CPU phase
    printf(1, "[MIXED %d] CPU phase %d\n", pid, i + 1);
    for(j = 0; j < 500000; j++){
      asm("nop");
    }
    
    // I/O phase
    printf(1, "[MIXED %d] I/O phase %d\n", pid, i + 1);
    sleep(3);
  }
  
  printf(1, "[MIXED %d] Completed!\n", pid);
  exit();
}
