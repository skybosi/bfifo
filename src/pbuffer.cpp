#include "fifo.h"
//Pbuffer::_bufferMaxSize = 10;
Pbuffer::Pbuffer():_bufferMaxSize(10),_size(0)
{
	member = new char[_bufferMaxSize];
}

Pbuffer::~Pbuffer()
{
	if(member) delete []member; 
}

int Pbuffer::writeBuffer()
{
	if(!isFull())
	{
		cout << "please input data：";
		cin >> member;
		_size = strlen(member);
		if(isFull())
			cout << "\tis full...\n";
	}
	else
		cout << "\tis full...\n";
	return _size;
}
int Pbuffer::readBuffer()
{
	int size = _size;
	if(!isEmpty())
	{
		cout << "buffer have:" << member << endl;
		_size = 0;
	}
	else;
		//cout << "\tis empty...\n";
	return size;
}

bool Pbuffer::isEmpty()
{
	//return _size <= 0;
	if( _size <= 0)
		return true;
	return false;
}

bool Pbuffer::isFull()
{
	//return _bufferMaxSize >= _size;
	if(_size > _bufferMaxSize)
		return true;
	return false;
}
