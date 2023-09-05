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

/* Obtain temperature information measured by DS18B20 */
int Get_DS18B20_Temp(double *temp) {
	int 			 fd = -1;
	int 			 rv = -1;
	char 			 path[50] = "/sys/bus/w1/devices/";
	char			 dir_name[20];
	int				 found = -1;
	DIR 			*dirp;
	struct dirent	*direntp;
	char 			 buf[128];
	char			*ptr;
	

	memset(dir_name, 0, sizeof(dir_name));
	memset(buf, 0, sizeof(buf));

	//open folder "/sys/bus/w1/devices/"
	if ((dirp = opendir(path)) == NULL) {
		printf("ERROR: Open Directory '%s' Failure: %s\n", path, strerror(errno));
		return -1;
	}
	printf("Open Directory '%s' Successfully\n", path);
	
	//find 28-xx
	while ((direntp = readdir(dirp)) != NULL) {
		if (strstr(direntp->d_name, "28-") == NULL)
			continue;
		
		strncpy(dir_name, direntp->d_name, strlen(direntp->d_name));
		printf("Find file: %s\n", dir_name);
		found = 1;
		break;
	}
	closedir(dirp);

	if (found == -1) {
		printf("ERROR: Can not find DS18B20 in %s\n", path);
		return -2;
	}
	
	// Concatenate the folder name and file name to the path	
	strncat(path, dir_name, strlen(dir_name));
	strncat(path, "/w1_slave", sizeof(path)-strlen(path));
	
	// open w1_slave file
	if ((fd = open(path, O_RDONLY)) < 0) {
		printf("ERROR: Open file '%s' Failure: %s\n", path, strerror(errno));
		return -3;
	}
	printf("Open file '%s' fd[%d] Successfully\n", path, fd);
	
	// read data from w1_slave
	if ((rv = read(fd, buf, sizeof(buf))) < 0) {
		printf("ERROR: Read data from file '%s' Failure: %s\n", path, strerror(errno));
		rv = -4;
		goto cleanup;
	}
	printf("Read %dB data from file '%s'\n", rv, path);
	
	if ((ptr = strstr(buf, "t=") + 2) == NULL) {
		printf("ERROR: Find data Failure: %s", strerror(errno));
		rv = -5;
		goto cleanup;
	}
	
	// Convert the data to double, divide by 1000 to get the normal decimal temperature
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