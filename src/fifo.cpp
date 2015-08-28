#include "fifo.h"
sem_t chg_sem;
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
	while(1)
	{
		printf("waiting write......\n");
		buff.writeBuffer();
		sem_wait(&chg_sem);
	}
	return 0;
}

void *watchDog(void *arg)
{
	while(1)
	{
		Pbuffer* elem = (Pbuffer*)arg;
//		printf("reading begin......\n");
		if(elem->readBuffer())
			sem_post(&chg_sem);
		else
			sleep(1);
	}
	return (void*)0;
}

