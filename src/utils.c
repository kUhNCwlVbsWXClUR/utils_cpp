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


void print_hex_ascii_line(const u_char* payload, int len, int offset)
{

	int i;
	int gap;
	const u_char* ch;

	/* offset */
	printf("%05d   ", offset);

	/* hex */
	ch = payload;
	for (i = 0; i < len; i++) {
		printf("%02x ", *ch);
		ch++;
		/* print extra space after 8th byte for visual aid */
		if (i == 7)
			printf(" ");

	}
	/* print space to handle line less than 8 bytes */
	if (len < 8)
		printf(" ");

	/* fill hex gap with spaces if not full line */
	if (len < 16) {
		gap = 16 - len;
		for (i = 0; i < gap; i++) {
			printf("   ");

		}

	}
	printf("   ");

	/* ascii (if printable) */
	ch = payload;
	for (i = 0; i < len; i++) {
		if (isprint(*ch))
			printf("%c", *ch);
		else
			printf(".");
		ch++;

	}

	printf("\n");

	return;

}

void print_payload(const u_char* payload, int len)
{

	int len_rem = len;
	int line_width = 16;            /* number of bytes per line */
	int line_len;
	int offset = 0;                 /* zero-based offset counter */
	const u_char* ch = payload;

	if (len <= 0)
		return;

	/* data fits on one line */
	if (len <= line_width) {
		print_hex_ascii_line(ch, len, offset);
		return;

	}

	/* data spans multiple lines */
	for (;; ) {
		/* compute current line length */
		line_len = line_width % len_rem;
		/* print line */
		print_hex_ascii_line(ch, line_len, offset);
		/* compute total remaining */
		len_rem = len_rem - line_len;
		/* shift pointer to remaining bytes to print */
		ch = ch + line_len;
		/* add offset */
		offset = offset + line_width;
		/* check if we have line width chars or less */
		if (len_rem <= line_width) {
			/* print last line and get out */
			print_hex_ascii_line(ch, len_rem, offset);
			break;

		}

	}

	return;

}

