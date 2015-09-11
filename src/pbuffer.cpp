#include "fifo.h"
//Pbuffer::_bufferMaxSize = 10;
Pbuffer::Pbuffer():_bufferMaxSize(10), _size(0)
{

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
	buffer_lock(&symbol_buffer);
	if(!isFull())
	{
		member[_size++] = ch;
		cout << member[_size-1] << " ";
	}
	buffer_unlock(&symbol_buffer);
	return _size;
}
int Pbuffer::readBuffer()
{
	buffer_lock(&symbol_buffer);
	int i = 0;
	if(!isEmpty())
	{
//		cout << "<<W | R>>(tid:) " << tid <<" [ ";
		cout << "<<W | R>> " <<" [ ";
		while(_size > 0 && i < _size) 
		{ 
			cout.put(member[i++]); 
			cout << " "; 
		} 
		memset(member,0,_bufferMaxSize);
		_size = 0 ; 
		cout << "]";
		cout << endl; 
		usleep(1);
	}
	buffer_unlock(&symbol_buffer);
	return i;
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
