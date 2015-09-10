#ifndef _FIFO_H_
#define _FIFO_H_
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;
class Pbuffer
{
	private:
		const int _bufferMaxSize;	
		char* member;
		int	_size;
		int symbol_buffer;
		unsigned long int lock;
	public:
		Pbuffer();
		~Pbuffer();
		int size();
		int CompareAndExchange(int *ptr,int olddata, int newdata);
		void buffer_lock(int* symbol);
		void buffer_unlock(int* symbol);
		bool isEmpty();
		bool isFull();
		int  writeBuffer(char);
		bool setlock();
		int	 readBuffer();		//read data from buffer if have data
		char* getBuffer();
};

#endif
