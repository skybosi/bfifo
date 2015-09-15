#include "fifo.h"
void *watchDog(void *arg);
int main(int argc,char** argv)
{
	if(argc < 2)
	{
		cout << "usage: " << argv[0] << " thread count (eg: 1)" << endl;
		return 0;
	}
	int threads = atoi(argv[1]);
	int nums = 0;
	Pbuffer buff;
	pthread_t pth[threads];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);//线程分离属性
	while(nums < threads)
	{
		if(pthread_create(&pth[nums++],&attr,watchDog,(void *)&buff)!=0)		//创建一个线程
		{
			perror("ptread_create error");
			exit(1);
		}
	}
	int i = 0;
	char test[12] = "0123456789\n";
	while(1)
	{
		//cout << "write in:" ;
		while(test[i])
		{
			buff.writeBuffer(test[i++]);
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
		//cout << "\t0 thread read: ";
		elem->readBuffer();
	}
	return (void*)0;
}

//fifio.cpp
