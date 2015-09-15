#include "pbuffer.h"
unsigned int __stdcall watchDog(PVOID arg);

int main(int argc,char** argv)
{
   
    Pbuffer buff;  
	const int THREAD_NUM = 2;
	HANDLE	handle[THREAD_NUM];
	for (int i = 0; i < THREAD_NUM; i++)  
		 handle[i] = (HANDLE)_beginthreadex(NULL, 0, watchDog, (LPVOID)&buff, 0, NULL);
    int i = 0;
    char test[12] = "0123456789\n";
    while(1)
    {   
        while(test[i])
        {   
            buff.writeBuffer(test[i++]);
        }   
        i = 0;
    }
	WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);  
    return 0;
}

unsigned int __stdcall watchDog(PVOID arg)
{
    while(1)
    {
        Pbuffer* elem = (Pbuffer*)arg;
        //cout << "\t0 thread read: ";
        elem->readBuffer();
    }
    return 0;
}

//fifio.cpp