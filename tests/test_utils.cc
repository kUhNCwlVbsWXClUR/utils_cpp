#include<utils_cpp/utils.h>
#include<fcntl.h>

/*
 * 获取文件大小的三个版本
 *
 */

int main4(){
	const char *filename = "test.pcm";
	// int filesize = getFileSizeC(filename);
	int filesize = getFileSizeL(filename);
	if (filesize==-1){
		printf("open %s fail.\n", filename);
	}

}


int main1(){

	char *buf = currTime("%Y-%m-%d %H:%M:%S");
	printf("%s\n", buf);

	return 0;

}

int main2(int argc, char *argv[]){
	int ret;
	ret = copy(argv[1], argv[2]);
	if (ret!=0){
		printf("copy failed\n");
	}
	return 0;
}

int main(){

	char filename[] = "libutils.a.bak";
    int fd = open(filename, O_RDONLY);
    if(fd == -1){
        printf("open %s failed..\n", filename);
        return -1;
    }
	unsigned char buf[64] = {1, 2, 3};

	int ret = read(fd, buf, 64);
	printf("read %d bytes from file\n", ret);
	
	print_payload(buf, 64);

}
