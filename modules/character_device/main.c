#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define EEP_NBANK       4
#define EEP_DEVICE_NAME "dev-fortytwo"
#define EEP_CLASS       "dev-fortytwo"

struct class    *eep_class;
struct cdev     eep_cdev[EEP_NBANK];
dev_t           dev_num;

static int __init ft_module_init(void)
{
    int     i;
    dev_t   curr_dev;

    alloc_chrdev_region(&dev_num, 0, EEP_NBANK, EEP_DEVICE_NAME);
    eep_class = class_create(THIS_MODULE, EEP_CLASS);
    for (i = 0; i < EEP_NBANK; ++i) {
        cdev_init(&eep_cdev[i], &eep_fops);
        eep_cdev[i].owner = THIS_MODULE;
        curr_dev = MKDEV(MAJOR(dev_num), MINOR(dev_num) + i);
        cdev_add(&eep_cdev[i], curr_dev, 1);
        device_create(eep_class,
                        NULL,
                        curr_dev,
                        NULL,
                        EEP_DEVICE_NAME "%d", i);
    }
    return 0;
}

static void __exit ft_module_exit(void)
{
    unregister_chrdev_region(dev_num, EEP_NBANK);
}

module_init(ft_module_init);
module_exit(ft_module_exit);
