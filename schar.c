#include "schar.h"

/**
 * 这是模块的入口
 */
int init_module(void){
	LOG("schar....init_module.....");
	file_op.read = schar_read;
	file_op.write = schar_write;
	file_op.open = schar_open;
	file_op.release = schar_release;
	//注册字符设备
	int res = register_chrdev(MAJOR_SCHAR, NAME_SCHAR, &file_op);
        if(res < 0){
		LOG("注册设备驱动程序发生了错误...");
	}else{
		LOG("注册设备驱动程序成功....");
	}
	LOG("res = %d\n", res);
	return res;
}	

/**
 * 清理模块
 */
void cleanup_module(void){
	printk(KERN_DEBUG "good bye kernel\n");
	//注销注册字符设备
	unregister_chrdev(MAJOR_SCHAR, NAME_SCHAR);
}


/**
 * 打开设备的函数声明
 */
static int schar_open(struct inode* pnode, struct file* pfile){
	LOG("schar_open.....");
	//try_module_get(THIS_MODULE);
	if(pfile->f_mode & FMODE_READ){
		LOG("以只读模式打开....");
	}
}

/**
 * 释放设备的函数声明
 */
static int schar_release(struct inode* pnode, struct file* pfile){
	//module_put(THIS_MODULE);//名字前面没有try，和get不同
	LOG("schar_release.....");
}

/**
 * 从设备中读取数据的函数声明
 */
static ssize_t schar_read(struct file* pfile, char* buf, size_t count, loff_t* offset){


}

/**
 * 向设备写数据的函数声明
 */
static ssize_t schar_write(struct file* pfile, const char* buf, size_t count, loff_t* offset){


}



