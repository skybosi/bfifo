#include "fifo.h"
sem_t chg_sem;
void *watchDog(void *arg);
int main(int argc,char** argv)
{
	pthread_t pth;
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
		printf("waiting write......\n");
		fgets(test,BUFFER_SIZE + 1,stdin);
//		printf("{len :%d}\n",strlen(test));
		test[strlen(test)] = 0;
//		printf("{%c}\n",test[BUFFER_SIZE]);
//		sleep(2);
		sem_wait(&chg_sem);
	}
	return 0;
}

bool writeElem(elem_t* elem)
{
	int i = 0;
	while(elem[i])
		printf("[%d]\t",elem[i++]);
	memset(elem,0,BUFFER_SIZE);
	return TRUE;
}

bool haveData(elem_t* elem)
{
	int i = 0;
	while(elem[i] && i < BUFFER_SIZE + 1)
	{
		if(elem[i] != 0)
		{
//			printf("have data ......\n");
			return TRUE;
		}
	}
//	printf("not have data ......\n");
	return FALSE;
}

void *watchDog(void *arg)
{

	while(1)
	{
//		printf("chlid the thread......\n");
//		sem_post(&chg_sem);
		elem_t* elem = (elem_t*)arg;
		if(haveData(elem))
		{
			printf("reading begin......\n");
			writeElem(elem);
			sem_post(&chg_sem);
		}
		else
		{
//			sleep(1);
		}
	}
}

