/*
  Copyright (c) 2023 Radxa Ltd.
  Author: Nascs <nascs@radxa.com>
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
//#include <fcntl.h>
//#include <sys/ioctl.h>
//#include <linux/spi/spidev.h>
#include "wiringx.h"

#define	TRUE	(1==1)
#define	FALSE	(!TRUE)

#define	SPI_CHAN		0
#define	NUM_TIMES		100
#define	MAX_SIZE		(1024*1024)

static int myFd ;


void spiSetup (int speed) {
	if ((myFd = wiringXSPISetup (SPI_CHAN, speed)) < 0) {
		fprintf (stderr, "Can't open the SPI bus: %s\n", strerror (errno)) ;
		exit (EXIT_FAILURE) ;
	}
}


int main (void) {

	int speed, times, size ;
	unsigned int start, end ;
	int spiFail ;
	unsigned char *myData ;
	double timePerTransaction, perfectTimePerTransaction, dataSpeed ;

	if ((myData = malloc (MAX_SIZE)) == NULL) {
	  fprintf (stderr, "Unable to allocate buffer: %s\n", strerror (errno)) ;
		exit (EXIT_FAILURE) ;
	}

	if(wiringXSetup("radxa_e23", NULL) == -1) {
		wiringXGC();
		return -1;	
	}

	for (speed = 1 ; speed <= 32 ; speed *= 2) {

		printf ("+-------+--------+----------+----------+-----------+------------+\n") ;
		printf ("|   MHz |   Size | mS/Trans |      TpS |    Mb/Sec | Latency mS |\n") ;
		printf ("+-------+--------+----------+----------+-----------+------------+\n") ;

		spiFail = FALSE ;
		spiSetup (speed * 1000000) ;
		for (size = 1 ; size <= MAX_SIZE ; size *= 2) {
			printf ("| %5d | %6d ", speed, size) ;

			start = usleep(500);
			for (times = 0 ; times < NUM_TIMES ; ++times)
				if (wiringXSPIDataRW (SPI_CHAN, myData, size) == -1) {
					printf ("SPI failure: %s\n", strerror (errno)) ;
					spiFail = TRUE ;
					break ;
				}
			end = usleep(500);

			if (spiFail)
				break ;

			timePerTransaction        = ((double)(end - start) / (double)NUM_TIMES) / 1000.0 ;
			dataSpeed                 =  (double)(size * 8)    / (1024.0 * 1024.0) / timePerTransaction  ;
			perfectTimePerTransaction = ((double)(size * 8))   / ((double)(speed * 1000000)) ;

			printf ("| %8.3f ", timePerTransaction * 1000.0) ;
			printf ("| %8.1f ", 1.0 / timePerTransaction) ;
			printf ("| %9.5f ", dataSpeed) ;
			printf ("|   %8.5f ", (timePerTransaction - perfectTimePerTransaction) * 1000.0) ;
			printf ("|\n") ;

		}

		close (myFd) ;
		printf ("+-------+--------+----------+----------+-----------+------------+\n") ;
		printf ("\n") ;
	}

	return 0 ;}
