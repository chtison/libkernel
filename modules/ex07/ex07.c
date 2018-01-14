#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/debugfs.h>
#include <linux/jiffies.h>
#include <linux/spinlock.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chtison");
MODULE_DESCRIPTION("Useless module");

static struct dentry * dir_fortytwo;
static struct dentry * file_jiffies;
static struct dentry * file_foo;

static char		foo[PAGE_SIZE];
static loff_t	foo_size = 0;
static rwlock_t	foo_lock = __RW_LOCK_UNLOCKED(foo_lock);

static ssize_t ft_file_foo_read(struct file *file, char __user *buf, size_t len, loff_t *offs) {
	ssize_t ret;

	read_lock(&foo_lock);
	ret = simple_read_from_buffer(buf, len, offs, foo, foo_size);
	read_unlock(&foo_lock);
	return ret;
}

static ssize_t ft_file_foo_write(struct file *file, const char __user *buf, size_t len, loff_t *offs) {
	ssize_t ret;

	write_lock(&foo_lock);
	ret = simple_write_to_buffer(foo, PAGE_SIZE, offs, buf, len);
	write_unlock(&foo_lock);
	if (*offs > foo_size)
		foo_size = *offs;
	return ret;
}

static struct file_operations fops_file_foo = {
	.owner	= THIS_MODULE,
	.read	= &ft_file_foo_read,
	.write	= &ft_file_foo_write,
};

static void __exit ft_exit(void)
{
	debugfs_remove_recursive(dir_fortytwo);
}

static int __init ft_init(void)
{
	if ((dir_fortytwo = debugfs_create_dir("fortytwo", NULL)) == NULL) {
		printk(KERN_ERR "debugfs_create_dir returned NULL");
		return -ENOMSG;
	} else if (dir_fortytwo == ERR_PTR(-ENODEV)) {
		printk(KERN_ERR "debugfs_create_dir returned -ENODEV");
		return -ENODEV;
	}

	// Only works as expected on 64 bits
	if ((file_jiffies = debugfs_create_u64("jiffies", 0444, dir_fortytwo, (u64 *)&jiffies)) == NULL) {
		printk(KERN_ERR "debugfs_create_u64 returned NULL");
		ft_exit();
		return -ENOMSG;
	} else if (dir_fortytwo == ERR_PTR(-ENODEV)) {
		printk(KERN_ERR "debugfs_create_u64 returned -ENODEV");
		ft_exit();
		return -ENODEV;
	}

	if ((file_foo = debugfs_create_file("foo", 0644, dir_fortytwo, NULL, &fops_file_foo)) == NULL) {
		printk(KERN_ERR "debugfs_create_file returned NULL");
		ft_exit();
		return -ENOMSG;
	} else if (dir_fortytwo == ERR_PTR(-ENODEV)) {
		printk(KERN_ERR "debugfs_create_file returned -ENODEV");
		ft_exit();
		return -ENODEV;
	}

	return 0;
}

module_init(ft_init);
module_exit(ft_exit);
