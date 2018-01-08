/* *************************************************************************
Author: Mahesh Gautam
Date: 3/10/14
Class: CS 450
Assignment: Project2
Instructor: Michael Lyle
Description: This is a LINUX Kernel Module which lists all the task by performing
a depth first search
*******************************************************************************
*/  

#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/slab.h>
 
static void dfs(struct task_struct* dftask); 

static int simple_init(void){

  struct task_struct *task; 
  struct list_head *list;

  list_for_each(list, &init_task.children){
    task = list_entry(list, struct task_struct, sibling);
    printk("%s,%d\n", task->comm, task->pid); 
    dfs(task);                                                                                                                                                                        
  }
                                                                                     
/* // FOR PART ONE                                                                                                     
for_each_process(task){                                                                                                        
//  on each iteration task points to the next task                                                                             
  printk("Name: %s PID: [%d]\n", task->comm, task->pid);                                                                  
}*/                                                                                                                                                                                                 
  return 0;                                                                                                                           
}                                                                                                                                                                                     
//Perform depth first search
static void dfs(struct task_struct* dftask){
  struct task_struct *temp; 
  struct list_head *list; 
  list_for_each(list, &dftask->children){
    temp= list_entry(list, struct task_struct, sibling); 
    printk("%s, %d\n", temp->comm, temp->pid); 
    dfs(temp); 
  }
}

//clean up
static void simple_exit(void){
  printk("Removing Module"); 
}

//start - end
module_init(simple_init); 
module_exit(simple_exit); 
