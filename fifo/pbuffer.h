#ifndef _PBUFFER_H_
#define _PBUFFER_H_

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <process.h>   
using namespace std;
class Pbuffer
{

//#define  ATOMIC_INIT(i) {(i)}
    private:
        const int _bufferMaxSize;   
        char* member;
        int _size;
		volatile long m_lock;
    protected:
        static int lock;
        static int unlock;
    public:
        Pbuffer();
        ~Pbuffer();
        int size();
        bool isEmpty();
        bool isFull();
        int  writeBuffer(char);
        int  readBuffer();      //read data from buffer if have data
        char* getBuffer();
};

#endif //_PBUFFER_H_