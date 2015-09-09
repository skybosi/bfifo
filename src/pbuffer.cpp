#include "fifo.h"
//Pbuffer::_bufferMaxSize = 10;
Pbuffer::Pbuffer():_bufferMaxSize(10), _size(0)
{
	read_lock = 0;
	write_lock = 0;
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
	if(!isFull())
	{
		if(!symbol_buffer)
		{
			symbol_buffer++;
			member[_size++] = ch;
			cout << member[_size-1] << " ";
			symbol_buffer--;
		}
		return _size;
	}
	else
	{
		//cout << "\tbuffer is full...\n";
		return 0;
	}
}
int Pbuffer::readBuffer()
{
	if(!isEmpty())
	{
		int i = 0; 
		if(!symbol_buffer)
		{
			symbol_buffer++;
			cout << "<<W | R>>(_size:) "<< _size<<" [ ";
			while(i < _size) 
			{ 
				cout.put(member[i++]); 
				cout << " "; 
			} 
			memset(member,0,_bufferMaxSize);
			_size = 0 ; 
			cout << "]";
			cout << endl; 
			symbol_buffer--;
		}
		return i;
	}
	else
	{
		//cout << "\tbuffer is empty...\n";
		usleep(100);
		return 0;
	}
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
