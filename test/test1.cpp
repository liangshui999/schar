#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
using namespace std;

#define DEV_NAME "/dev/schar"

/**
 * 必须有管理员权限才能打开
 * 也就是运行的时候必须加上sudo
 * sudo ./test1
 */
void test1(){
	int fd = open(DEV_NAME, O_RDWR);
	if(fd == -1){
		cout << "设备打开失败...." << endl;
		exit(EXIT_FAILURE);
	}
	char buf[30];
	int rd_len = read(fd, buf, 8);
	cout << "rd_len = " << rd_len << endl;
	cout << "从设备中读取 buf = " << buf << endl;
	const char* wr_content = "from test1 "; 
	int wr_len = write(fd, wr_content, strlen(wr_content));
	cout << "wr_len = " << wr_len << endl;
}

int main(){

	test1();
	return 0;
}
