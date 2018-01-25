// Tasnim Noshin
// Umme Salma Gadriwala

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

void print_init_PCB(void) {
  int pid = init_task.pid;
  long state = init_task.state;
  printk(KERN_INFO "name: %s, state: %ld, pid:%d", init_task.comm, state, pid);
  
}


/* This function is called when the module is loaded. */
int simple_init(void)
{ printk(KERN_INFO "Loading Module\n");
  print_init_PCB();
  return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void)
{ printk(KERN_INFO "Removing Module\n");
}
/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");


