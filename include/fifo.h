#ifndef _FIFO_H_
#define _FIFO_H_

#include <stdio.h>
#include <string.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<semaphore.h>

#ifndef bool
#define bool	int
#define TRUE	1
#define FALSE	0
#endif
/*
typedef sturct elem
{
	char member;
	int	_size;

}elem_t;
*/
typedef char elem_t;
#define BUFFER_SIZE 10
bool haveData(elem_t* elem);
bool readElem(elem_t* elem);
//bool watchDog();


#endif
