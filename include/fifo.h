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
		const int _bufferMaxSize;	//buffer的最大容量（字节）
		char* member;				//buffer的地址
		int	_size;					//已写入的数据个数
		int symbol_buffer;			//用于同步的标志
	protected:
		static int lock;			
		static int unlock;
	public:
		Pbuffer();
		~Pbuffer();
		int size();
		bool isEmpty();				//判空
		bool isFull();				//判满
		int  writeBuffer(char);		//写入数据
		int	 readBuffer();			//read data from buffer if have data
};

#endif
