#ifndef _FIFO_H_
#define _FIFO_H_
#include <iostream>
#include <stdio.h>
#include <string.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<semaphore.h>
#define BUFFER_SIZE 10
using namespace std;
class Pbuffer
{
	private:
		const int _bufferMaxSize;	
		char* member;
		int	_size;
		sem_t chg_sem;
	public:
		Pbuffer();
		~Pbuffer();
		void wait_read();
		void post_read();
		bool isEmpty();
		bool isFull();
		int  writeBuffer();		//write data to buffer if no full
		int	 readBuffer();		//read data from buffer if have data
		char* getBuffer();
};

#endif
