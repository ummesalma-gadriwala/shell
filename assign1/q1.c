// Tasnim Noshin
// Umme Salma Gadriwala

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/types.h>


void print_dfs(struct task_struct *task) {
  printk(KERN_INFO "name: %s, state: %ld, pid:%d", task->comm, task->state, task->pid); // print this task
  
  struct task_struct *child;
  struct list_head *list;
  
  // list is the pointer to the current element
  // task->chilren is the head of the list
  list_for_each(list, &task-> children) {
    child = list_entry(list, struct task_struct, sibling);
    print_dfs(child);
  }
  
}


/* This function is called when the module is loaded. */
int simple_init(void)
{ printk(KERN_INFO "Loading Module\n");
  print_dfs(&init_task);
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


