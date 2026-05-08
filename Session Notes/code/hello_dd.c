#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "hello_device"
#define BUFFER_SIZE 1024

static int major_number;
static char message[] = "Hello from kernel driver!\n";
static int message_size = sizeof(message);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SVD");
MODULE_DESCRIPTION("Simple Hello World Character Driver");
MODULE_VERSION("1.0");

/* Called when device is opened */
static int device_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "hello_driver: Device opened\n");
    return 0;
}

/* Called when device is closed */
static int device_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "hello_driver: Device closed\n");
    return 0;
}

/* Called when user reads from device */
static ssize_t device_read(struct file *flip,
                           char __user *buffer,
                           size_t length,
                           loff_t *offset)
{
    int bytes_read = 0;

    if (*offset >= message_size)
        return 0;

    while (length && *offset < message_size) {
        put_user(message[*offset], buffer++);
        length--;
        (*offset)++;
        bytes_read++;
    }

    return bytes_read;
}

/* File operations structure */
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .read = device_read,
    .release = device_release,
};

/* Module initialization */
static int __init hello_init(void)
{
    major_number = register_chrdev(0, DEVICE_NAME, &fops);

    if (major_number < 0) {
        printk(KERN_ALERT "Failed to register character device\n");
        return major_number;
    }

    printk(KERN_INFO "hello_driver: Registered with major number %d\n",
           major_number);

    return 0;
}

/* Module cleanup */
static void __exit hello_exit(void)
{
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "hello_driver: Module unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
