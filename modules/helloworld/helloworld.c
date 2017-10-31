#include <linux/kernel.h>
#include <linux/module.h>

static int __init helloworld_init(void) {
    printk(KERN_INFO "Hello World !\n");
    return 0;
}

static void __exit helloworld_exit(void) {
    printk(KERN_INFO "Goodbye World !\n");
}

module_init(helloworld_init);
module_exit(helloworld_exit);
