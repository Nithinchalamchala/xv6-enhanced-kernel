#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "x86.h"
#include "traps.h"
#include "spinlock.h"

// Interrupt descriptor table (shared by all CPUs).
struct gatedesc idt[256];
extern uint vectors[];  // in vectors.S: array of 256 entry pointers
struct spinlock tickslock;
uint ticks;

// MLFQ boost tracking
#define BOOST_INTERVAL 1000  // Boost every 1000 ticks (~10 seconds)
static uint boost_timer = 0;
static int mlfq_debug = 0;  // Debug mode off by default
extern struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

void
tvinit(void)
{
  int i;

  for(i = 0; i < 256; i++)
    SETGATE(idt[i], 0, SEG_KCODE<<3, vectors[i], 0);
  SETGATE(idt[T_SYSCALL], 1, SEG_KCODE<<3, vectors[T_SYSCALL], DPL_USER);

  initlock(&tickslock, "time");
}

void
idtinit(void)
{
  lidt(idt, sizeof(idt));
}

//PAGEBREAK: 41
void
trap(struct trapframe *tf)
{
  if(tf->trapno == T_SYSCALL){
    if(myproc()->killed)
      exit();
    myproc()->tf = tf;
    syscall();
    if(myproc()->killed)
      exit();
    return;
  }

  switch(tf->trapno){
  case T_IRQ0 + IRQ_TIMER:
    if(cpuid() == 0){
      acquire(&tickslock);
      ticks++;
      wakeup(&ticks);
      release(&tickslock);
      
      // MLFQ: Check for priority boost
      boost_timer++;
      if(boost_timer >= BOOST_INTERVAL){
        acquire(&ptable.lock);
        struct proc *p;
        for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
          if(p->state != UNUSED){
            p->priority = 0;
            p->ticks_used = 0;
            p->wait_ticks = 0;
          }
        }
        release(&ptable.lock);
        boost_timer = 0;
        if(mlfq_debug)
          cprintf("[MLFQ] Priority boost - all processes moved to queue 0\n");
      }
    }
    lapiceoi();
    break;
  case T_IRQ0 + IRQ_IDE:
    ideintr();
    lapiceoi();
    break;
  case T_IRQ0 + IRQ_IDE+1:
    // Bochs generates spurious IDE1 interrupts.
    break;
  case T_IRQ0 + IRQ_KBD:
    kbdintr();
    lapiceoi();
    break;
  case T_IRQ0 + IRQ_COM1:
    uartintr();
    lapiceoi();
    break;
  case T_IRQ0 + 7:
  case T_IRQ0 + IRQ_SPURIOUS:
    cprintf("cpu%d: spurious interrupt at %x:%x\n",
            cpuid(), tf->cs, tf->eip);
    lapiceoi();
    break;

  //PAGEBREAK: 13
  default:
    if(myproc() == 0 || (tf->cs&3) == 0){
      // In kernel, it must be our mistake.
      cprintf("unexpected trap %d from cpu %d eip %x (cr2=0x%x)\n",
              tf->trapno, cpuid(), tf->eip, rcr2());
      panic("trap");
    }
    // In user space, assume process misbehaved.
    cprintf("pid %d %s: trap %d err %d on cpu %d "
            "eip 0x%x addr 0x%x--kill proc\n",
            myproc()->pid, myproc()->name, tf->trapno,
            tf->err, cpuid(), tf->eip, rcr2());
    myproc()->killed = 1;
  }

  // Force process exit if it has been killed and is in user space.
  // (If it is still executing in the kernel, let it keep running
  // until it gets to the regular system call return.)
  if(myproc() && myproc()->killed && (tf->cs&3) == DPL_USER)
    exit();

  // MLFQ: Handle timer tick for running process
  if(myproc() && myproc()->state == RUNNING &&
     tf->trapno == T_IRQ0+IRQ_TIMER){
    struct proc *p = myproc();
    p->ticks_used++;
    p->total_runtime++;
    
    // Check if process used up its quantum
    int quantum;
    if(p->priority == 0) quantum = 4;       // High priority
    else if(p->priority == 1) quantum = 8;  // Medium priority
    else quantum = 16;                      // Low priority
    
    if(p->ticks_used >= quantum){
      // Demote to lower priority if not already at lowest
      if(p->priority < 2){
        p->priority++;
        if(mlfq_debug)
          cprintf("[MLFQ] Process %d (%s) demoted to queue %d\n", 
                  p->pid, p->name, p->priority);
      }
      p->ticks_used = 0;
      yield();  // Give up CPU
    }
  }

  // Check if the process has been killed since we yielded
  if(myproc() && myproc()->killed && (tf->cs&3) == DPL_USER)
    exit();
}
