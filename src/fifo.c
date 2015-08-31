#include "fifo.h"
#include <time.h>
sem_t chg_sem;
void *watchDog(void *arg);
int main(int argc,char** argv)
{
	int t = 0;
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
	printf("waiting write......\n");
	while(1)
	{

		//fgets(test,BUFFER_SIZE + 1,stdin);
		srand(time(NULL));  /*初始化随机数种子*/
		t = rand()%3;
		switch(t)
		{
			case 0:
				strcpy(test,"0123456");
				break;
			case 1:
				strcpy(test,"0123456789");
				break;
			case 2:
				strcpy(test,"0123456789-=");
				break;
			default:
				break;
		}
		printf("data: %s\n",test);
		sem_post(&chg_sem);
		sleep(3);
	}
	return 0;
}

void *watchDog(void *arg)
{
	while(1)
	{
		//	printf("chlid the thread......\n");
		sem_wait(&chg_sem);
		elem_t* elem = (elem_t*)arg;
		if(haveData(elem))
		{
			printf("buffer have data! read begin......\n");
			if(readElem(elem))
				memset(elem,0,BUFFER_SIZE);
		}
		else
		{
			printf("no data...\r");
			sleep(1);
		}
	}
}

bool readElem(elem_t* elem)
{
	int i = 0;
	while(elem[i]&& i < BUFFER_SIZE)
	{
//		printf("\033[1;32m[%c]\033[0m",elem[i++]);
		printf("[%c] ",elem[i++]);
//		elem[i-1]  = 0;
	}
	printf("\n\n");
	return TRUE;
}

bool haveData(elem_t* elem)
{
	int i = 0;
	while(elem[i] && i < BUFFER_SIZE + 1)
	{
		if(elem[i] != 0)
		{
			//	printf("have data ......\n");
			return TRUE;
		}
	}
	//	printf("not have data ......\n");
	return FALSE;
}

