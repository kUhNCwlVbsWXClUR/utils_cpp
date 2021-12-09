#include<utils_cpp/utils.h>

/*
 * 获取文件大小的三个版本
 *
 */

int main(){
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
