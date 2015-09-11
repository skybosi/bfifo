#include "fifo.h"
void *watchDog(void *arg);
void *watchDog1(void *arg);
int main(int argc,char** argv)
{
	Pbuffer buff;
	pthread_t pth;
//	pthread_t pth1;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);//线程分离属性
	if(pthread_create(&pth,&attr,watchDog,(void *)&buff)!=0)		//创建一个线程
	{
		perror("ptread_create error");
		exit(1);
	}
/*	if(pthread_create(&pth1,&attr,watchDog1,(void *)&buff)!=0)		//创建一个线程
	{
		perror("ptread_create error");
		exit(1);
	}*/
	int i = 0;
	char test[11] = "0123456789";
	while(1)
	{
		//cout << "write in:" ;
		while(test[i])
		{
			buff.writeBuffer(test[i++]);
			//sleep(1);
			/*	buff.showBuffer(); cout << "(" << i << ")"; */
		}
		i = 0;
	}
	return 0;
}

void *watchDog(void *arg)
{
	//pthread_t tid = pthread_self();
	while(1)
	{
		Pbuffer* elem = (Pbuffer*)arg;
		//		cout << "\t0 thread read: ";
		elem->readBuffer();
		//sleep(1);
	}
	return (void*)0;
}
/*
void *watchDog1(void *arg)
{
	while(1)
	{
		Pbuffer* elem = (Pbuffer*)arg;
		//		cout << "\t1 thread read: ";
		elem->readBuffer();
		//sleep(1);
	}
	return (void*)0;
}*/
//fifio.cpp
