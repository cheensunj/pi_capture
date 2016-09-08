#include<unistd.h>
#include<linux/videodev2.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#define	DEV "/dev/video0"		//设备名
#define HEIGHT 640		//图像高度
#define WIDTH 480		//图像宽度

const char dev[]={"/dev/video0"};
int main(int argc, char* argv[]){
	int fd;	
	if((fd = open(dev,O_RDWR)) == -1){
		printf("error: cannot open %s\n",dev);
		return -1;
	}
	printf("fd is: %d\n",fd);
	struct v4l2_capability cap;
	if(ioctl(fd,VIDIOC_QUERYCAP,&cap ) == -1){
		printf("error: cannot querycap --VIDIOC_QUERYCAP\n");
	}
	else {
		printf("Driver: %s\n",cap.driver);
		printf("Card: %s\n",cap.card);
		printf("Bus_info: %d\n",cap.bus_info);
		printf("Version: %d\n",cap.version);
		printf("Capabilities: %x\n",cap.capabilities);
	}

	close(fd);
}
