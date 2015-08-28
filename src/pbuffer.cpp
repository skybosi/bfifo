#include "fifo.h"
//Pbuffer::_bufferMaxSize = 10;
Pbuffer::Pbuffer():_bufferMaxSize(5),_size(0)
{
	member = new char[_bufferMaxSize];
	if(sem_init(&chg_sem, 0, 0) != 0)  
	{  
		perror("semaphore intitialization failed\n");  
		exit(EXIT_FAILURE);  
	} 
}

Pbuffer::~Pbuffer()
{
	if(member) delete []member; 
	sem_destroy(&chg_sem); 
}

int Pbuffer::writeBuffer()
{
	if(!isFull())
	{
		while(1)
		{
			member[_size] = cin.get();
			_size++;
			if(isFull()|| member[_size-1] == '\n')
			{
				break;
			}
		}
	}
	else;
		//cout << "\tis full...\n";
	return _size;
}
int Pbuffer::readBuffer()
{
	if(!isEmpty())
	{
		int i = 0;
		cout << "before _size:" << _size << endl;
		while(_size)
		{
			cout.put(member[i++]);
			_size-- ;
		}
		cout << "\naftre _size:" << _size << endl;
		return i;
//		if(_size > _bufferMaxSize)
//			readBuffer();
	}
	else
		return 0;
		//cout << "\tis empty...\n";
}

bool Pbuffer::isEmpty()
{
	return _size <= 0;
}

bool Pbuffer::isFull()
{
	return _bufferMaxSize < _size;
}

char* Pbuffer::getBuffer()
{
	return member;
}

void Pbuffer::wait_read()
{
	sem_wait(&chg_sem);
}

void Pbuffer::post_read()
{
	sem_post(&chg_sem);
}
