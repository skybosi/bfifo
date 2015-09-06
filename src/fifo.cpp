#include "fifo.h"
void *watchDog(void *arg);
int main(int argc,char** argv)
{
	Pbuffer buff;
	pthread_t pth;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);//线程分离属性
	if(pthread_create(&pth,&attr,watchDog,(void *)&buff)!=0)		//创建一个线程
	{
		perror("ptread_create error");
		exit(1);
	}
	int i = 0;
	char test[12] = "0123456789\n";
	while(1)
	{
		while(test[i])
		{
			buff.writeBuffer(test[i++]);
			/*	buff.showBuffer(); cout << "(" << i << ")"; */
		}
		i = 0;
	}
	return 0;
}

void *watchDog(void *arg)
{
	while(1)
	{
		Pbuffer* elem = (Pbuffer*)arg;
		//cout << "\tchild thread read:\t";
		elem->readBuffer();
	}
	return (void*)0;
}
//fifio.cpp
