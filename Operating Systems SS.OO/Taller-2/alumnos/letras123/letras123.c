#include <linux/init.h>
#include <linux/module.h>   // THIS_MODULE
#include <linux/kernel.h>   // printk
#include <linux/fs.h>       // File operations
#include <linux/cdev.h>     // Char devices
#include <linux/device.h>   // device_create
#include <linux/uaccess.h>  // copy_to_user, copy_from_user
#include <linux/slab.h>     // kmalloc, kfree
#include <linux/spinlock.h> // spinlock

#define SLOT_COUNT 3

// Contador global de slots usados, protegido del acceso concurrente con spinlock.
static spinlock_t lock;
// Contador global de slots disponibles.
static int slots_available = SLOT_COUNT;

// Almacena los datos por proceso que abre el dispositivo:
typedef struct user_data
{
    // Marca si ya se escribio un caracter valido.
    bool valid;
    // Caracter escrito por el usuario.
    char input;
} user_data;

static int letras_open(struct inode *inod, struct file *filp)
{
    unsigned long flags;
    user_data *udata;

    // Disminuye el contador si hay espacios disponibles, o falla con -EPERM si no hay:

    // Protegido por spinlock.
    spin_lock_irqsave(&lock, flags);
    if (slots_available == 0)
    {
        spin_unlock_irqrestore(&lock, flags);
        return -EPERM;
    }

    // Reserva un espacio.
    slots_available--;
    spin_unlock_irqrestore(&lock, flags);

    // Asigna memoria para la estructura del proyecto.
    udata = kmalloc(sizeof(user_data), GFP_KERNEL);
    // En caso de error, se libera el espacio reservado.
    if (!udata)
    {
        spin_lock_irqsave(&lock, flags);
        slots_available++;
        spin_unlock_irqrestore(&lock, flags);
        return -ENOMEM;
    }

    // Aun no se escribio nada.
    udata->valid = false;
    // Guarda el estado por proceso.
    filp->private_data = udata;

    return 0;
}

// Libera el slot ocupado y la memoria privada del proceso:
static int letras_release(struct inode *inod, struct file *filp)
{
    unsigned long flags;

    if (filp->private_data)
    {
        kfree(filp->private_data);
        filp->private_data = NULL;

        spin_lock_irqsave(&lock, flags);
        // Libera al slot ocupado.
        slots_available++;
        spin_unlock_irqrestore(&lock, flags);
    }

    return 0;
}

// Devuelve al usuario una repeticion del caracter escrito:
static ssize_t letras_read(struct file *filp, char __user *data, size_t size, loff_t *offset)
{
    user_data *udata = (user_data *)filp->private_data;
    char *kbuf;

    // Si aun no se escribio ningun dato, falla con -EPERM.
    if (!udata || !udata->valid)
        return -EPERM;

    // Crea un buffer en el kernel del tamaño solicitado.
    kbuf = kmalloc(size, GFP_KERNEL);
    if (!kbuf)
        return -ENOMEM;

    // Llena el buffer con el caracter guardado.
    memset(kbuf, udata->input, size);

    // Copia el buffer al espacio de usuario.
    if (copy_to_user(data, kbuf, size))
    {
        kfree(kbuf);
        return -EFAULT;
    }

    kfree(kbuf);
    // Retorna la cantidad de caracteres leidos.
    return size;
}

// Guarda un unico caracter enviado por el usuario
static ssize_t letras_write(struct file *filp, const char __user *data, size_t size, loff_t *offset)
{
    user_data *udata = (user_data *)filp->private_data;
    char ch;

    if (!udata)
        return -EPERM;

    // Ignora escrituras subsecuentes.
    // Si ya se escribio, se ignora.
    if (udata->valid)
        return size;

    if (copy_from_user(&ch, data, 1))
        return -EFAULT;

    udata->input = ch;
    udata->valid = true;

    return size;
}

// Estructura que define las operaciones del dispositivo.
static struct file_operations letras_fops = {
    .owner = THIS_MODULE,
    .open = letras_open,
    .read = letras_read,
    .write = letras_write,
    .release = letras_release,
};

// Globales del dispositivo:

static dev_t letras_devno;
static struct cdev letras_cdev;
static struct class *letras_class;

static int __init letras_init(void)
{
    // Inicializa el spinlock. 
    spin_lock_init(&lock);

    // Registra un numero mayor y menor dinamico.
    if (alloc_chrdev_region(&letras_devno, 0, 1, "SO-letras123") < 0)
        return -1;

    // Inicializa cdev.
    cdev_init(&letras_cdev, &letras_fops);
    if (cdev_add(&letras_cdev, letras_devno, 1) < 0)
        goto unregister;

    letras_class = class_create(THIS_MODULE, "letras123");
    if (IS_ERR(letras_class))
        goto del_cdev;

    if (device_create(letras_class, NULL, letras_devno, NULL, "letras123") == NULL)
        goto destroy_class;

    printk(KERN_ALERT "Loading module 'letras123'\n");
    return 0;

destroy_class:
    class_destroy(letras_class);
del_cdev:
    cdev_del(&letras_cdev);
unregister:
    unregister_chrdev_region(letras_devno, 1);
    return -1;
}

static void __exit letras_exit(void)
{
    printk(KERN_ALERT "Unloading module 'letras123'\n");

    // Elimina el dispositivo y se liberan recursos:

    device_destroy(letras_class, letras_devno);
    class_destroy(letras_class);
    cdev_del(&letras_cdev);
    unregister_chrdev_region(letras_devno, 1);
}

module_init(letras_init);
module_exit(letras_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("La banda de SO");
MODULE_DESCRIPTION("Generador de letras con sincronización");
