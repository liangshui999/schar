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
#include<linux/uaccess.h>

MODULE_LICENSE("GPL");

#define DEBUG
#ifdef DEBUG
#define LOG(format, args...) printk(KERN_DEBUG "schar : "format, ##args)
#else
#define LOG(format, args...)
#endif

#define MAJOR_SCHAR 42
#define NAME_SCHAR "schar"

#define BASE_TYPE 0xbb
#define READ_POOL_COUNT _IOR(BASE_TYPE, 0, int)
#define SET_POOL_COUNT _IOW(BASE_TYPE, 1, int)


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

/**
 * 对设备进行io控制
 */
static long schar_unlocked_ioctl(struct file* pfile, unsigned int \
		command, unsigned long arg);

static struct file_operations file_op; 
