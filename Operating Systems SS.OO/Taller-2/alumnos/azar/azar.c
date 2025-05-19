#include <linux/init.h>
#include <linux/module.h>  // THIS_MODULE
#include <linux/kernel.h>  // Kernel cosas
#include <linux/fs.h>      // File operations
#include <linux/cdev.h>    // Char devices
#include <linux/device.h>  // Nodos filesystem
#include <linux/uaccess.h> // copy_to_user
#include <linux/slab.h>    // kmalloc
#include <linux/random.h>  // get_random_bytes
#include <linux/kernel.h>  // kstrtoint, snprintf

static int upper_bound = -1;

static ssize_t azar_write(struct file *filp, const char __user *data, size_t size, loff_t *offset)
{
    char *kernel_buf;
    int ret;

    // +1 para '\0'.
    kernel_buf = kmalloc(size + 1, GFP_KERNEL);
    if (!kernel_buf)
        return -ENOMEM;

    // Copia de espacio de usuario a kernel, convierte el string a entero y guarda el valor.
    if (copy_from_user(kernel_buf, data, size))
    {
        kfree(kernel_buf);
        return -EFAULT;
    }

    // Asegura que la string este terminada.
    kernel_buf[size] = '\0';

    // Conversion a entero.
    ret = kstrtoint(kernel_buf, 10, &upper_bound);
    kfree(kernel_buf);

    // Si no es un numero, falla con -EPERM.
    if (ret < 0)
        return -EPERM;

    return size;
}

static ssize_t azar_read(struct file *filp, char __user *data, size_t size, loff_t *offset)
{
    // Buffer del numero aleatorio como string.
    char output[16];
    unsigned int rand;
    int len;

    // Si no hay upper_bound, falla con -EPERM.
    if (upper_bound <= 0)
        return -EPERM;

    // Si hay, genera numero aleatorio entre 0 y upper_bound,
    get_random_bytes(&rand, sizeof(rand));
    rand %= upper_bound;
    // Y formatea el numero como string terminado en '\n'.
    len = snprintf(output, sizeof(output), "%u\n", rand);

    if (size < len)
        return -EINVAL;

    // Devuelve el string al espacio de usuario.
    if (copy_to_user(data, output, len))
        return -EFAULT;

    return len;
}

static struct file_operations azar_fops =
{
    .owner = THIS_MODULE,
    .read = azar_read,
    .write = azar_write,
};

static dev_t azar_devno;
static struct cdev azar_cdev;
static struct class *azar_class;

static int __init azar_init(void)
{
    cdev_init(&azar_cdev, &azar_fops);
    alloc_chrdev_region(&azar_devno, 0, 1, "SO-azar");
    cdev_add(&azar_cdev, azar_devno, 1);

    azar_class = class_create(THIS_MODULE, "azar");
    device_create(azar_class, NULL, azar_devno, NULL, "azar");

    printk(KERN_ALERT "Loading module 'azar'\n");
    return 0;
}

static void __exit azar_exit(void)
{
    printk(KERN_ALERT "Unloading module 'azar'\n");

    // Elimina el dispositivo y se liberan recursos:

    device_destroy(azar_class, azar_devno);
    class_destroy(azar_class);

    unregister_chrdev_region(azar_devno, 1);
    cdev_del(&azar_cdev);
}

module_init(azar_init);
module_exit(azar_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("La banda de SO");
MODULE_DESCRIPTION("Generador de números al azar");
