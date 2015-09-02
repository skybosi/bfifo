#include "fifo.h"
//Pbuffer::_bufferMaxSize = 10;
Pbuffer::Pbuffer():_bufferMaxSize(10), _size(0)
{
	member = new char[_bufferMaxSize + 1];
	member[_bufferMaxSize] = '\0';
	cout << "new a array!" << endl;
	if(sem_init(&chg_sem, 0, 0) != 0)  
	{  
		perror("semaphore intitialization failed\n");  
		exit(1);  
	} 
}

Pbuffer::~Pbuffer()
{
	sem_destroy(&chg_sem); 
	if(member)
	{
		cout << "delete a array!" << endl;
		delete []member; 
	}
}

int Pbuffer::writeBuffer()
{
	if(!isFull())
	{
		/*while(1)
		  {
		  member[_size] = cin.get();
		  _size++;
		  if(isFull()|| member[_size-1] == '\n')
		  {
		  break;
		  }
		  }*/
		strcpy(member,"0123456789");
		_size =  strlen(member);
	}
	else;
	//cout << "\tis full...\n";
	return _size;
}
int Pbuffer::writeBuffer(char ch)
{
	if(!isFull())
	{
		_size = (_size) % _bufferMaxSize;
		member[_size++] = ch;
		return _size;
	}
	else
	{
		cout << "\tbuffer is full...\n";
		return 0;
	}
}
int Pbuffer::readBuffer()
{
	if(!isEmpty())
	{
		cout << "[";
		int i = 0;
		while(i < _bufferMaxSize)
		{
			cout.put(member[i++]);
			cout << " ";
			//			_size-- ;
		}
		cout << "]";
		cout << endl;
		return i;
	}
	else
	{
		cout << "\tbuffer is empty...\n";
		return 0;
	}
}
void Pbuffer::showBuffer()
{
	cout << "_size : " << _size << "\twrite in data: " << member << endl;
}
int Pbuffer::size()
{
	return _bufferMaxSize;
}

void Pbuffer::wait_read()
{
	sem_wait(&chg_sem);
}

void Pbuffer::post_read()
{
	sem_post(&chg_sem);
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

