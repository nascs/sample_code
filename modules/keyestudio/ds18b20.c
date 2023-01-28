#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int Get_DS18B20_Temp(double *temp);

/* 获取DS18B20测量的温度信息 */
int Get_DS18B20_Temp(double *temp) {
	int 			 fd = -1;
	int 			 rv = -1;
	char 			 path[50] = "/sys/bus/w1/devices/";
	char			 dir_name[20];
	int				 found = -1;
	DIR 		    *dirp;
	struct dirent	*direntp;
	char 			 buf[128];
	char			*ptr;
	
	//清空dir_name和buf内存空间的值，避免随机值产生乱码
	memset(dir_name, 0, sizeof(dir_name));
	memset(buf, 0, sizeof(buf));

	//打开文件夹"/sys/bus/w1/devices/"
	if ((dirp = opendir(path)) == NULL) {
		printf("ERROR: Open Directory '%s' Failure: %s\n", path, strerror(errno));
		return -1;
	}
	printf("Open Directory '%s' Successfully\n", path);
	
	//在文件夹中找DS18B20的文件夹28-xx
	while ((direntp = readdir(dirp)) != NULL) {
		if (strstr(direntp->d_name, "28-") == NULL)
			continue;
		
		strncpy(dir_name, direntp->d_name, strlen(direntp->d_name));
		printf("Find file: %s\n", dir_name);
		found = 1;
		break;
	}
	closedir(dirp);
	
	//找不到该文件夹
	if (found == -1) {
		printf("ERROR: Can not find DS18B20 in %s\n", path);
		return -2;
	}
	
	//将文件夹名和文件名分别拼接到path上	
	strncat(path, dir_name, strlen(dir_name));
	strncat(path, "/w1_slave", sizeof(path)-strlen(path));
	
	//打开w1_slave文件
	if ((fd = open(path, O_RDONLY)) < 0) {
		printf("ERROR: Open file '%s' Failure: %s\n", path, strerror(errno));
		return -3;
	}
	printf("Open file '%s' fd[%d] Successfully\n", path, fd);
	
	//从w1_slave中读取内容
	if ((rv = read(fd, buf, sizeof(buf))) < 0) {
		printf("ERROR: Read data from file '%s' Failure: %s\n", path, strerror(errno));
		rv = -4;
		goto cleanup;
	}
	printf("Read %dB data from file '%s'\n", rv, path);
	
	//从buf里匹配"t="，并将ptr移到数据的首地址上
	if ((ptr = strstr(buf, "t=") + 2) == NULL) {
		printf("ERROR: Find data Failure: %s", strerror(errno));
		rv = -5;
		goto cleanup;
	}
	
	//将数据转为double型，除1000得到正常的十进制温度
	*temp = atof(ptr)/1000;

cleanup:
	if (fd > 0)
		close(fd);

	return rv;
}

/* The main function */
int main(int argc, char **argv) {
	double	temp;
	
	if (Get_DS18B20_Temp(&temp) < 0) {
		printf("ERROR: DS18B20 Get Temperature Failure\n");
		return -1;
	}
	printf("Temperature is: %.3f C\n", temp);
	
	return 0;
}