// MLFQ Scheduler Test
// Spawns multiple processes with different workload characteristics

#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid1, pid2, pid3, pid4;
  
  printf(1, "\n");
  printf(1, "========================================\n");
  printf(1, "MLFQ SCHEDULER TEST\n");
  printf(1, "========================================\n");
  printf(1, "This test spawns multiple processes:\n");
  printf(1, "- 2 CPU-bound processes (should be demoted)\n");
  printf(1, "- 1 I/O-bound process (should stay high priority)\n");
  printf(1, "- 1 Mixed workload process\n");
  printf(1, "\n");
  printf(1, "Watch for [MLFQ] messages showing:\n");
  printf(1, "- Process demotion to lower queues\n");
  printf(1, "- Priority boosts\n");
  printf(1, "- Aging promotions\n");
  printf(1, "========================================\n\n");
  
  // Spawn CPU-bound process 1
  pid1 = fork();
  if(pid1 == 0){
    exec("cpubound", (char*[]){ "cpubound", 0 });
    printf(2, "exec cpubound failed\n");
    exit();
  }
  
  sleep(5);  // Small delay
  
  // Spawn I/O-bound process
  pid2 = fork();
  if(pid2 == 0){
    exec("iobound", (char*[]){ "iobound", 0 });
    printf(2, "exec iobound failed\n");
    exit();
  }
  
  sleep(5);  // Small delay
  
  // Spawn CPU-bound process 2
  pid3 = fork();
  if(pid3 == 0){
    exec("cpubound", (char*[]){ "cpubound", 0 });
    printf(2, "exec cpubound failed\n");
    exit();
  }
  
  sleep(5);  // Small delay
  
  // Spawn mixed workload process
  pid4 = fork();
  if(pid4 == 0){
    exec("mixed", (char*[]){ "mixed", 0 });
    printf(2, "exec mixed failed\n");
    exit();
  }
  
  // Wait for all children
  printf(1, "\n[TEST] All processes spawned. Waiting for completion...\n\n");
  
  wait();
  wait();
  wait();
  wait();
  
  printf(1, "\n========================================\n");
  printf(1, "MLFQ TEST COMPLETED\n");
  printf(1, "========================================\n");
  printf(1, "Check the output above for:\n");
  printf(1, "1. CPU-bound processes being demoted\n");
  printf(1, "2. I/O-bound process staying responsive\n");
  printf(1, "3. Priority boosts occurring\n");
  printf(1, "4. Fair CPU distribution\n");
  printf(1, "========================================\n\n");
  
  exit();
}
