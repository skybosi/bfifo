#include "pbuffer.h"
//Pbuffer::_bufferMaxSize = 10;
int Pbuffer::lock = 0;
int Pbuffer::unlock = 1;
Pbuffer::Pbuffer():_bufferMaxSize(10), _size(0),m_lock(0)
{
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
   //     while (!(__sync_bool_compare_and_swap (&symbol_buffer,lock, 1) )); 
	//while(InterlockedExchange(&m_lock,TRUE)==TRUE);
  while( InterlockedCompareExchange( &m_lock, 1 , 0) != 0 ); 
    if(!isFull())
		
    {   
        member[_size++] = ch; 
    }   
	    InterlockedExchange(&m_lock, 0);
     //   __sync_bool_compare_and_swap (&symbol_buffer, unlock, 0); 
    return _size;
}
int Pbuffer::readBuffer()
{
      // while (!(__sync_bool_compare_and_swap (&symbol_buffer,lock, 1) )); 
	//while(InterlockedExchange(&m_lock,TRUE)==TRUE);
	while( InterlockedCompareExchange( &m_lock, 1 , 0) != 0);
    int i = 0;
    if(!isEmpty())
    {   
        while(_size > 0 && i < _size)
        {
            cout.put(member[i++]);
            cout << " ";
        }
        memset(member,0,_bufferMaxSize);
        _size = 0 ;
    }
	InterlockedExchange(&m_lock, 0);
      //  __sync_bool_compare_and_swap (&symbol_buffer, unlock, 0);
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

char* Pbuffer::getBuffer()
{
    return member;
}
//pbuffer.cpp