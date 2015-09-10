#include "fifo.h"
//Pbuffer::_bufferMaxSize = 10;
Pbuffer::Pbuffer():_bufferMaxSize(10), _size(0)
{
	lock = 0;
	symbol_buffer = 0;
	member = new char[_bufferMaxSize];
	cout << "new a array!" << endl;
}

Pbuffer::~Pbuffer()
{
	if(member)
	{
		cout << "delete a array!" << endl;
		delete []member; 
	}
}

int Pbuffer::writeBuffer(char ch)
{
	pthread_t tid = pthread_self();
	if(lock == tid)
	{
		if(!isFull())
		{
			buffer_lock(&symbol_buffer);
			member[_size++] = ch;
			cout << member[_size-1] << " ";
			buffer_unlock(&symbol_buffer);
		}
	}
	return _size;
}
int Pbuffer::readBuffer()
{
	pthread_t tid = pthread_self();
	int i = 0; 
	if(lock == tid)
	{
		if(!isEmpty())
		{
			buffer_lock(&symbol_buffer);
			cout << "<<W | R>> "<<" [ ";
			while(_size > 0 && i < _size) 
			{ 
				cout.put(member[i++]); 
				cout << " "; 
			} 
			memset(member,0,_bufferMaxSize);
			_size = 0 ; 
			cout << "]";
			cout << endl; 
			buffer_unlock(&symbol_buffer);
			usleep(1);
		}
	}
	return i;
}
bool Pbuffer::setlock()
{
	pthread_t tid = pthread_self();
	lock = tid;
	return true;
}

void Pbuffer::buffer_lock(int* symbol) 
{
	while(CompareAndExchange(symbol, 0, 1) == 1); 
}

void Pbuffer::buffer_unlock(int* symbol) 
{
	*symbol = 0;
}

int Pbuffer::CompareAndExchange(int *ptr, int olddata, int newdata)
{
	int actual = *ptr;
	if (actual == olddata)
		*ptr = newdata;
	return actual;
}

int Pbuffer::size()
{
	return _bufferMaxSize;
}

bool Pbuffer::isEmpty()
{
	return _size <= 0;
}

bool Pbuffer::isFull()
{
	return _bufferMaxSize <= _size;
}

char* Pbuffer::getBuffer()
{
	return member;
}
//pbuffer.cpp
