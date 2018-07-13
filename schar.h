#include<linux/module.h>

#ifdef CONFIG_SMP
#define _SMP_
#endif

#ifdef CONFIG_MODVERSIONS
#define MODVERSIONS
#include<linux/modversions.h>
#endif

#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/fs.h>

MODULE_LICENSE("GPL");

#define DEBUG
#ifdef DEBUG
#define LOG(format, args...) printk(KERN_DEBUG "schar : "format, ##args)
#else
#define LOG(format, args...)
#endif

#define MAJOR_SCHAR 42
#define NAME_SCHAR "schar"

/**
 * 打开设备的函数声明
 */
static int schar_open(struct inode* pnode, struct file* pfile);

/**
 * 释放设备的函数声明
 */
static int schar_release(struct inode* pnode, struct file* pfile);

/**
 * 从设备中读取数据的函数声明
 */
static ssize_t schar_read(struct file* pfile, char* buf, size_t count, loff_t* offset);

/**
 * 向设备写数据的函数声明
 */
static ssize_t schar_write(struct file* pfile, const char* buf, size_t count, loff_t* offset);

static struct file_operations file_op; 
