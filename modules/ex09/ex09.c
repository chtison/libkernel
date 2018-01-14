#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include "ex09.h"

MODULE_LICENSE("gpl");

static const char * ent_name __initconst = "mymounts";

static void * ft_start(struct seq_file *m, loff_t *pos) {
}

static void ft_stop(struct seq_file *m, void *v) {

}

static void * ft_next(struct seq_file *m, void *v, loff_t *pos) {

}

static int ft_show(struct seq_file *m, void *v) {

}

static const struct seq_operations seq_ops = {
	.start	= &ft_start,
	.stop	= &ft_stop,
	.next	= &ft_next,
	.show	= &ft_show,
}

static int ft_open(struct inode *inode, struct file *file) {
	return seq_open(file, seq_ops);
}

static struct proc_dir_entry  *	ent;
static const struct file_operations ent_fops = {
	.owner	= THIS_MODULE,
	.open	= &ft_open,
};

static int __init ft_init(void)
{
	if (unlikely((ent = proc_create(ent_name, 0444, NULL, &ent_fops)) == NULL)) {
		printk(KERN_ERR "proc_create(\"%s\", 0444, NULL, &fops) returned NULL", ent_name);
		return (-ENOMSG);
	}
	return 0;
}

static void __exit ft_exit(void)
{
	proc_remove(ent);
}

module_init(ft_init);
module_exit(ft_exit);
