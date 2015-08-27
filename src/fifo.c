#include "fifo.h"
//sem_t chg_sem;
static _size = 0;
void *watchDog(void *arg);
int main(int argc,char** argv)
{
	int i = 0;
	pthread_t pth;
	elem_t one = 0;
	elem_t test[BUFFER_SIZE] = { 0 };
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);//线程分离属性
	if(pthread_create(&pth,&attr,watchDog,(void *)test)!=0)		//创建一个线程
	{
		perror("ptread_create error");
		exit(1);
	}
	while(1)
	{
		printf("main the thread......\n");
/*		one = getchar();
		test[i++] = one;
		if(i > BUFFER_SIZE)
			break;*/
//		memcpy(test,"testing!",10);
		fgets(test,BUFFER_SIZE + 1,stdin);
		test[strlen(test) - 1] = 0;
		sleep(2);
	}
	return 0;
}

bool writeElem(elem_t* elem)
{
	int i = 0;
	while(elem[i])
	printf("[%c]\t",elem[i++]);
	memset(elem,0,BUFFER_SIZE);
}

void *watchDog(void *arg)
{

	while(1)
	{
		printf("chlid the thread......\n");
//		sem_post(&chg_sem);
		elem_t* elem = (elem_t*)arg;
		writeElem(elem);

		/*
		   int size  = (int)arg;
		   printf("size: %d\n",size);
		   if(size != _size)
		   {
		   _size =  size;
		   writeElem();
		   }
		   else
		   printf("haha\n");
		 */
//		sleep(2);
	}
}

