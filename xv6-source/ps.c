#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"

int
main(int argc, char *argv[])
{
  int pid, priority, ticks, state;
  uint runtime;
  char name[16];
  char *states[] = {"unused", "embryo", "sleep", "runble", "run", "zombie"};
  
  printf(1, "PID  STATE   PRI  TICKS  RUNTIME  NAME\n");
  printf(1, "---  ------  ---  -----  -------  ----\n");
  
  // Try to get info for PIDs 1-64 (NPROC)
  for(pid = 1; pid <= 64; pid++){
    if(getprocinfo(pid, &priority, &ticks, &runtime, &state, name) == 0){
      printf(1, "%-4d %-6s  %d    %-5d  %-8d %s\n", 
             pid, states[state], priority, ticks, runtime, name);
    }
  }
  
  exit();
}
