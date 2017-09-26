/*
E/13/058
De Silva M.D.R.A.M
co327 project
part 02
*/

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/sched.h>  


void depth_first_search_find(struct task_struct *task){
	
	struct list_head *list;  
	struct task_struct *next;  

	list_for_each(list, &task->children) {
		

		next= list_entry(list, struct task_struct, sibling);
		printk(KERN_INFO "[Pid: %d]: [Pname: %s]: [State: %ld]\n",next->pid, next->comm, next->state);

		depth_first_search_find(next);
	}
	
}

int init_depth_first_search(void){

	printk(KERN_INFO "Loading the module\n");

	depth_first_search_find(&init_task);
	return 0;
}	

void exit_depth_first_search(void){

	printk(KERN_INFO "Unloading module\n");
}

module_init(init_depth_first_search);
module_exit(exit_depth_first_search);


