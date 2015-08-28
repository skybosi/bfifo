#include "fifo.h"
//sem_t chg_sem;
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
	printf("\nwaiting write......\n");
	while(1)
	{
		buff.writeBuffer();
		if(!strcmp(buff.getBuffer(),"exit\n"))
			break;
	//	sleep(1);
		buff.post_read();
	}
	return 0;
}

void *watchDog(void *arg)
{
	while(1)
	{
		Pbuffer* elem = (Pbuffer*)arg;
		elem->wait_read();
		printf("\nreading begin......\n");
		if(!strcmp(elem->getBuffer(),"exit\n"))
			break;
		while(!elem->readBuffer());
		printf("\nwaiting write......\n");
	/*	int len = elem->readBuffer();
		if(len)
			printf("\nwaiting write......\n");
		else
		{
			printf("\nreading begin......\n");
		}*/
	}
	return (void*)0;
}
