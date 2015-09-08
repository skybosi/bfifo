#ifndef _FIFO_H_
#define _FIFO_H_
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#define GREEN   "\033[32m"      /* Green */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define ERROR 0
#define OK 1
using namespace std;
class Pbuffer
{
	private:
		const int _bufferMaxSize;	
		char* member;
		int	_size;
		int symbol_buffer;
	protected:
		int read_lock;
		int write_lock;
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
