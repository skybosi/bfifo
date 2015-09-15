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
<<<<<<< HEAD
	char member;
	int	_size;

}elem_t;
*/
typedef char elem_t;
#define BUFFER_SIZE 10
bool haveData(elem_t* elem);
bool readElem(elem_t* elem);
//bool watchDog();
=======
>>>>>>> Bfifo_sync

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
