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

	sig_wait();
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
		return 0;
	}
}
//int Pbuffer::sig_wait(sigset_t* sig, in*& signum)
int Pbuffer::sig_wait()
{
	int signum;
	sigset_t sig;
	sigemptyset(&sig);
	sigaddset(&sig,SIGUSR1);
	pthread_sigmask(SIG_BLOCK,&sig,NULL);//设置该线程的信号屏蔽字为SIGUSR1
	sigwait(&sig,&signum);//睡眠等待SIGUSR1信号的到来
	return signum;
}
bool Pbuffer::set_signal()
{
	struct sigaction act;
	act.sa_handler=SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	sigaction(SIGUSR1,&act,0);//设置信号SIGUSR1的处理方式忽略
	return true;
}
bool Pbuffer::send_signal(pthread_t& pth)
{
	 pthread_kill(pth,SIGUSR1);
	 return true;
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
