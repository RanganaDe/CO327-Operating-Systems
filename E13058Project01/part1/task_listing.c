/*
E/13/058
De Silva M.D.R.A.M
co327 project
part 01
*/


#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>


int init_task_listing(void){
	
	
	struct task_struct *task;

	for_each_process(task){
		printk(KERN_INFO "[Pid: %d]: [Pname: %s]: [State:%ld]\n", task->pid, task->comm, task->state);
	}
	
	return 0;
}

void exit_task_listing(void){

	printk(KERN_INFO "Unloading the module\n");
}

module_init(init_task_listing);
module_exit(exit_task_listing);

