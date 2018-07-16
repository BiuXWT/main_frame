#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<signal.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>          
#include<sys/socket.h>
#include<sys/wait.h>
#include<errno.h>


//third party libs

#include<cJSON.h>


#ifdef _DEBUG_MAIN
#define LOG(format, ...) fprintf(stdout, ">>>>>[%s]-[%s]-[%d] " format "<<<<\n",__FILE__,__FUNCTION__,__LINE__, ##__VA_ARGS__)
#else
#define LOG(format, ...)
#endif


#endif