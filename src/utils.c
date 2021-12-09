#include<utils_cpp/utils.h>


int getFileSizeC(const char* filename){
	/*
	 * c version 
	 * c版本获取文件大小
	 */
	printf("call getFileSize [C version]\n");

	unsigned long filesize = -1;

	if(filename == NULL){
		printf("%s is NULL", filename);
		return filesize;
	}
	FILE *fp = NULL;
	fp = fopen(filename, "r");
	if(fp==NULL){
		printf("file: %s open fail\n", filename);
		return filesize;
	}

	fseek(fp, 0L, SEEK_END);

	filesize = ftell(fp);  // 返回文件的位置

	// loc可以作为字节数
	printf("B: %lu\n", filesize);
	// printf("K: %lu\n", filesize/1024);
	// printf("M: %lu\n", filesize/1024/1024);
	// printf("G: %lu\n", filesize/1024/1024/1024);

	if(fp!=NULL){
		fclose(fp);
	}
	return filesize;
}

int getFileSizeU(const char* filename){
	printf("call getFileSize [Unix version]\n");
	unsigned long filesize = -1;
	int fd;
	fd = open(filename, O_RDONLY);
	if (fd ==-1){
		printf("%s open fail.", filename);
		return filesize;
	}

	off_t ret;
	ret = lseek(fd, 0, SEEK_END);
	if (ret == (off_t)-1){
		if(close(fd) == -1){
			printf("%s close fail.", filename);
		}
		return filesize;
	}
	filesize = ret;
	printf("B: %lu\n", filesize);

	if(close(fd) == -1){
		printf("%s close fail.", filename);
	}
	return filesize;

}

int getFileSizeL(const char* filename){
	printf("call getFileSize [L version]\n");

	unsigned long filesize = -1;
	struct stat st;

	if(filename == NULL){
		printf("%s is NULL", filename);
		return filesize;
	}
	stat(filename, &st);
	if(stat(filename, &st) == -1){
		return filesize;
	}

	filesize =(long long) st.st_size;
	printf("B: %lu\n", filesize);

	return filesize;

}

char *currTime(const char* format){
	static char buf[BUF_SIZE];
	time_t t;
	size_t s;
	struct tm *tm;
	
	t = time(NULL);
	tm = localtime(&t);
	if(tm ==NULL)
		return NULL;

	s = strftime(buf, BUF_SIZE, (format !=NULL) ? format : "%c", tm);
	return (s==0) ? NULL : buf;

}

int copy(const char* src, const char* dst){
	/*
	 * 文件访问模式
	 * O_RDONLY: 只读
	 * O_WRONLY: 只写
	 * O_RDWR:   读写
	 *
	 */
	int inputFd, outputFd;
	int openFlags, filePerms;
	int numRead;
	char buf[BUF_SIZE];
	int flags = O_RDONLY;
	inputFd = open(src, flags);
	if(inputFd == -1)
		return -1;
	
	// S_I
	// USR  user
	// GRP  group
	// OTH  other
	// R W  read write
	// rw-rw-rw
	openFlags = O_CREAT | O_WRONLY | O_TRUNC;
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	outputFd = open(dst, openFlags, filePerms);
	if(outputFd == -1){
		return -1;
	}

	while((numRead = read(inputFd, buf, BUF_SIZE)) >0 )
		if(write(outputFd, buf, numRead) != numRead)
			printf("write() returned error or partial write occurred\n");
	if(numRead == -1)
		return -1;
	printf("copy finished..\n");
	close(inputFd);
	close(outputFd);

	return 0;
}

