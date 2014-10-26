/*
 * $ gcc -Wall -Wextra RasPi_MCP3202.c -lwiringPi
 * Author: Toshihisa Tanaka <tosihisa@netfort.gr.jp>
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <signal.h>
#include <time.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#define MCP3202_STARTBIT    ((unsigned char)(0x01))
#define MCP3202_SGL_DIFF    ((unsigned char)(0x80))
#define MCP3202_ODD_SIGN    ((unsigned char)(0x40))
#define MCP3202_MSBF        ((unsigned char)(0x20))

int main(void)
{
	FILE *debugfp = stdout;
	unsigned char data[3];
	int channel = 0;
	unsigned short val[2];

	fprintf(debugfp,"%s:%d\n",__FILE__,__LINE__);

	if(wiringPiSetup () < 0)
	{
		fprintf(stderr,"wiringPiSetup failed\n");
		return 1;
	}
	if(wiringPiSPISetup(channel, 1000000) < 0)
	{
		fprintf(stderr,"wiringPiSPISetup failed\n");
		return 2;
 	}

	while(1){
		/* read CH0 */
		data[0] = MCP3202_STARTBIT;
		data[1] = MCP3202_SGL_DIFF | 0x0F;
		data[2] = 0xFF;
		wiringPiSPIDataRW(channel, data, sizeof(data));
		val[0] = (((unsigned short)(data[1])) << 8) | (unsigned short)(data[2]);
		val[0] &= (unsigned short)0x0FFF;

		/* read CH1 */
		data[0] = MCP3202_STARTBIT;
		data[1] = MCP3202_SGL_DIFF | MCP3202_ODD_SIGN | 0x0F;
		data[2] = 0xFF;
		wiringPiSPIDataRW(channel, data, sizeof(data));
		val[1] = (((unsigned short)(data[1])) << 8) | (unsigned short)(data[2]);
		val[1] &= (unsigned short)0x0FFF;

		fprintf(debugfp,"val: %4d , %4d\n",val[0],val[1]);
		sleep(1);
	}

	return 0;
}

