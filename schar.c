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
	file_op.unlocked_ioctl = schar_unlocked_ioctl;
	//将本驱动程序注册到指定的字符设备上面
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
 * 必须返回0才行，否则别人打开的时候会打开失败
 */
static int schar_open(struct inode* pnode, struct file* pfile){
	LOG("schar_open.....");
	//try_module_get(THIS_MODULE);
	if(pfile->f_mode & FMODE_READ){
		LOG("以读模式打开....");
	}
	if(pfile->f_mode & FMODE_WRITE){
		LOG("以写模式打开...");
	}
	return 0;
}

/**
 * 释放设备的函数声明
 */
static int schar_release(struct inode* pnode, struct file* pfile){
	//module_put(THIS_MODULE);//名字前面没有try，和get不同
	LOG("schar_release.....");
	return 0;
}

/**
 * 从设备中读取数据的函数声明
 * 这里的返回值，将会是read（）函数调用的返回值
 */
static ssize_t schar_read(struct file* pfile, char* buf, size_t count, loff_t* offset){
	LOG(" 客户端请求读取的长度 count = %d ", count);
	char* str = "abcdefg";
	//成功返回0，失败返回尚未读取的字节数
	unsigned long res = copy_to_user(buf, str, count);
	LOG("schar_read: res = %ld ", res);
	return count;
}

/**
 * 向设备写数据的函数声明
 */
static ssize_t schar_write(struct file* pfile, const char* buf, size_t count, loff_t* offset){
	LOG("schar_write: count = %d, buf = %s ", count, buf);
	return count;
}



/**
 * 对设备进行io控制
 * 参数arg是一个地址，因为客户端调用的时候传递过来的是一个地址
 * 因此arg可以强转为指针
 */
static long schar_unlocked_ioctl(struct file* pfile, unsigned int \
		command, unsigned long arg){
	int tmp = 1367;
	int* p = NULL;
	//检查魔术
	if(_IOC_TYPE(command) != BASE_TYPE){
		LOG("魔数不正确......\n");
		return -ENOTTY;
	}
	switch(command){
		case READ_POOL_COUNT:
			LOG("READ_POOL_COUNT.......\n");
			copy_to_user((int*)arg, &tmp, sizeof(tmp));
			p = (int*)arg;
			LOG("*p = %d ", *p);
			break;
		case SET_POOL_COUNT:
			LOG("SET_POOL_COUNT........\n");
			copy_from_user(&tmp, (int*)arg, sizeof(tmp));
			LOG("设置的pool_count = %d ", tmp);
			break;
	}
	return 0;
}















