#ifndef UTILS_CPP__H
#define UTILS_CPP__H

#ifdef __cplusplus
extern "C"
{
#endif


#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/time.h>
#include<time.h>


/*
 * 获取文件大小的三个版本
 *
 */

//const int BUF_SIZE =1024;
#define BUF_SIZE 1024

int getFileSizeC(const char* filename);

int getFileSizeU(const char* filename);

int getFileSizeL(const char* filename);

char *currTime(const char* format);

int copy(const char* src, const char* dst);

#ifdef __cplusplus
}
#endif

#endif // UTILS_CPP__H

