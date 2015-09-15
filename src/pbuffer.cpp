#include "fifo.h"
//Pbuffer::_bufferMaxSize = 10;
int Pbuffer::lock = 0;
int Pbuffer::unlock = 1;
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
	while (!(__sync_bool_compare_and_swap (&symbol_buffer,lock, 1) )); //上锁
	if(!isFull())
	{
		member[_size++] = ch;
//		cout << member[_size-1] << " ";
	}
	__sync_bool_compare_and_swap (&symbol_buffer, unlock, 0);		//解锁
	return _size;
}
int Pbuffer::readBuffer()
{
	while (!(__sync_bool_compare_and_swap (&symbol_buffer,lock, 1) )); //上锁
	int i = 0;
	if(!isEmpty())
	{
		//		cout << "<<W | R>>(tid:) " << tid <<" [ ";
//		cout << "<<W | R>> " <<" [ ";
		while(_size > 0 && i < _size) 
		{ 
			cout.put(member[i++]); 
			cout << " "; 
		} 
		memset(member,0,_bufferMaxSize);
		_size = 0 ; 
//		cout << "]";
		//cout << endl; 
	}
	__sync_bool_compare_and_swap (&symbol_buffer, unlock, 0);		//解锁
	return i;
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

//pbuffer.cpp
