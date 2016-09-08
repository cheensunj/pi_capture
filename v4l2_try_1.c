#include<unistd.h>
#include<linux/videodev2.h>
#include<stdio.h>
#include<fcntl.h>
//#include<sys/ioctl.h>
#define	DEV "/dev/video0"		//设备名
#define HEIGHT 640		//图像高度
#define WIDTH 480		//图像宽度

const char dev[]={"/dev/video0"};
int main(int argc, char* argv[]){
	const int fd  = open (dev,O_RDWR);	
	if(fd == -1){
		printf("error: cannot open %s\n",dev);
		return -1;
	}
	printf("fd is: %d\n",fd);
	struct v4l2_capability cap;
	if(ioctl(fd,VIDIOC_QUERYCAP,&cap ) == -1){
		printf("error: cannot querycap --VIDIOC_QUERYCAP\n");
		return -1;
	}
	else {
		printf("Driver: %s\n",cap.driver);
		printf("Card: %s\n",cap.card);
		printf("Bus_info: %d\n",cap.bus_info);
		printf("Version: %d\n",cap.version);
		printf("Capabilities: %x\n",cap.capabilities);
	}
	struct v4l2_fmtdesc fmtdesc;
	fmtdesc.index = 0;
	fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	while( ioctl(fd, VIDIOC_ENUM_FMT,&fmtdesc) != -1){
		printf("index: %d  description: %s\n",fmtdesc.index,fmtdesc.description);
		fmtdesc.index++;
	}
	struct v4l2_format format;
	format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	format.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
	format.fmt.pix.height = HEIGHT;
	format.fmt.pix.width = WIDTH;
	format.fmt.pix.field = V4L2_FIELD_INTERLACED;
	if(ioctl(fd, VIDIOC_S_FMT, &format) == -1){
		printf("Unable to set format!  --VIDIOC_S_FMT\n");
		return -1;
	}
	if(ioctl(fd, VIDIOC_G_FMT, &format) == -1){
		printf("Unable to get format!  --VIDIOC_G_FMT\n");
		return -1;
	}
	else {
		//print format...
	}

	//Begin capture! ---------------------------------------------
	struct v4l2_requestbuffers req;
	req.count = 4;
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_MMAP;
	if(ioctl(fd,VIDIOC_REQBUFS,&req)==-1){
		printf("request for buffers error\n");
	}
	close(fd);
}
