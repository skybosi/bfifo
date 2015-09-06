#include "fifo.h"
//Pbuffer::_bufferMaxSize = 10;
Pbuffer::Pbuffer():_bufferMaxSize(10), _size(0)
{
	member = new char[_bufferMaxSize + 1];
	member[_bufferMaxSize] = '\0';
	cout << "new a array!" << endl;
	if(pthread_mutex_init(&mutex,NULL) != 0)
	{
		perror("mutex intitialization failed\n");  
		exit(1);  
	}  
	if(sem_init(&chg_read, 0, 0) != 0)  
	{  
		perror("semaphore chg_read intitialization failed\n");  
		exit(1);  
	} 
	if(sem_init(&chg_write, 0, 0) != 0)  
	{  
		perror("semaphore chg_write intitialization failed\n");  
		exit(1);  
	} 
}

Pbuffer::~Pbuffer()
{
	pthread_mutex_destroy(&mutex);  
	sem_destroy(&chg_read); 
	sem_destroy(&chg_write); 
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
		/*while(1) { member[_size] = cin.get(); _size++; if(isFull()|| member[_size-1] == '\n') { break; } }*/
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
		Pwait(&chg_write);
		pthread_mutex_lock(&mutex); 
		_size = (_size) % _bufferMaxSize;
		member[_size++] = ch;
		pthread_mutex_unlock(&mutex); 
		Ppost(&chg_read);
		return _size;
	}
	else
	{
		cout << "\tbuffer is full...\n";
		Ppost(&chg_read);
		Pwait(&chg_write);
		return 0;
	}
}
int Pbuffer::readBuffer()
{
	if(!isEmpty())
	{
		Ppost(&chg_write);
		pthread_mutex_lock(&mutex); 
		/*cout << "["; int i = 0; while(i < _bufferMaxSize) { cout.put(member[i++]); cout << " "; //	_size-- ; } cout << "]"; cout << endl; */
		cout.put(member[_size-1]);
		//sleep(1);
		pthread_mutex_unlock(&mutex); 
		Pwait(&chg_read);
		return _size;
	}
	else
	{
		cout << "\tbuffer is empty...\n";
		Ppost(&chg_write);
		Pwait(&chg_read);
		return 0;
	}
}
void Pbuffer::showBuffer()
{
	pthread_mutex_lock(&mutex); 
	cout << "_size : " << _size << "\twrite in data: " << member << endl;
	pthread_mutex_unlock(&mutex); 
}
int Pbuffer::size()
{
	return _bufferMaxSize;
}

void Pbuffer::Pwait(sem_t* sem)
{
	sem_wait(sem);
}

void Pbuffer::Ppost(sem_t* sem)
{
	sem_post(sem);
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
//pbuffer.cpp
