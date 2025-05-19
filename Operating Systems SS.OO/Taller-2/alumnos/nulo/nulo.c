#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>

#define DEVICE_NAME "nulo"

static ssize_t nulo_read(struct file *filp, char __user *data, size_t s, loff_t *off)
{
    // Simula que no hay nada que leer, como /dev/null.
    return 0;
}

static ssize_t nulo_write(struct file *filp, const char __user *data, size_t s, loff_t *off)
{
    // Simula que acepta todos los bytes, como /dev/null
    return s;
}

// Estructura que define las operaciones read y write del dispositivo.
static struct file_operations nulo_operaciones =
{
    .owner = THIS_MODULE,
    .read = nulo_read,
    .write = nulo_write,
};

static struct cdev nulo_device;
static dev_t major;
static struct class *nulo_class;

static int __init hello_init(void)
{
    int err;

    // Reserva un numero mayor dinamico:
    err = alloc_chrdev_region(&major, 0, 1, DEVICE_NAME);
    if (err < 0)
    {
        printk(KERN_ALERT "No se pudo asignar major\n");
        return err;
    }

    // Inicializa y registra el dispositivo de caracteres cdev.
    cdev_init(&nulo_device, &nulo_operaciones);
    nulo_device.owner = THIS_MODULE;

    err = cdev_add(&nulo_device, major, 1);
    if (err < 0)
    {
        unregister_chrdev_region(major, 1);
        printk(KERN_ALERT "No se pudo agregar el cdev\n");
        return err;
    }

    // Crea clase para udev.
    nulo_class = class_create(THIS_MODULE, DEVICE_NAME);
    if (IS_ERR(nulo_class))
    {
        cdev_del(&nulo_device);
        unregister_chrdev_region(major, 1);
        printk(KERN_ALERT "No se pudo crear clase\n");
        return PTR_ERR(nulo_class);
    }

    // Crea el dispositivo en /nulo.
    device_create(nulo_class, NULL, major, NULL, DEVICE_NAME);

    printk(KERN_INFO "/dev/nulo cargado correctamente\n");
    return 0;
}

static void __exit hello_exit(void)
{
    // Elimina el dispositivo y se liberan recursos:

    device_destroy(nulo_class, major);
    class_destroy(nulo_class);
    cdev_del(&nulo_device);
    unregister_chrdev_region(major, 1);

    printk(KERN_INFO "/dev/nulo descargado\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("La banda de SO");
MODULE_DESCRIPTION("Una suerte de '/dev/null'");

// Compilar:
// make
// sudo insmod nulo.ko
// Tests:
// sudo python3 nulo_test.py
// Creacion del dispositivo:
// sudo mknod /dev/nulo c <major> 0
// sudo chmod 666 /dev/nulo