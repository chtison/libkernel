#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/fs.h>

static const char * login = "chtison\n";

static ssize_t ft_read(struct file *filep, char __user *buf, size_t len, loff_t *ppos) {
	return simple_read_from_buffer(buf, len, ppos, login, strlen(login));
}

static ssize_t ft_write(struct file *filep, const char __user *buf, size_t len, loff_t *ppos) {
	unsigned long	ret;
	char			tmp[strlen(login)];

	if (len != strlen(login))
		return -EINVAL;

	if ((ret = copy_from_user(tmp, buf, (unsigned long)len)))
		return -EFAULT;
	if ((strncmp(tmp, login, strlen(login))))
		return -EINVAL;
	return (ssize_t)strlen(login);
}

static const struct file_operations fops = {
	.owner	= THIS_MODULE,
	.read	= ft_read,
	.write	= ft_write,
};

static struct miscdevice device = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "fortytwo",
	.fops	= &fops,
};

static int __init ft_fortytwo_init(void)
{
	int err;

	if ((err = misc_register(&device)))
		return err;
	return 0;
}

static void __exit ft_fortytwo_exit(void)
{
	misc_deregister(&device);
}

module_init(ft_fortytwo_init);
module_exit(ft_fortytwo_exit);
