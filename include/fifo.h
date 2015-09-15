#ifndef _FIFO_H_
#define _FIFO_H_
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
using namespace std;
class Pbuffer
{
//#define  ATOMIC_INIT(i) {(i)}
	private:
		const int _bufferMaxSize;	
		char* member;
		int	_size;
		int symbol_buffer;
	protected:
		static int lock;
		static int unlock;
	public:
		Pbuffer();
		~Pbuffer();
		int size();
		bool isEmpty();
		bool isFull();
		int  writeBuffer(char);
		int	 readBuffer();		//read data from buffer if have data
		char* getBuffer();
};

#endif
