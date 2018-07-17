#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/ioctl.h>

#define BASE_TYPE 0xbb
#define READ_POOL_COUNT _IOR(BASE_TYPE, 0, int)
#define SET_POOL_COUNT _IOW(BASE_TYPE, 1, int)

#define DEV_NAME "/dev/schar"

using namespace std;

void test(){
	int fd = open(DEV_NAME, O_RDWR);
	if(fd == -1){
		cout << "字符设备打开失败" << endl;
		exit(EXIT_FAILURE);
	}
	cout << "fd = " << fd << endl;
	int tmp = 0;
	cout << "发起读取pool_count的调用... " << endl;
	//注意这边调用，参数部分传递的是地址
	int res = ioctl(fd, READ_POOL_COUNT, &tmp);
	cout << "tmp = " << tmp << endl;
	
	cout << "发起设置pool_count的调用........." << endl;
	int tmp2 = 754; 
	//注意这边调用，参数部分传递的是地址
	ioctl(fd, SET_POOL_COUNT, &tmp2);
}


int main(){

	test();
	return 0;
}
