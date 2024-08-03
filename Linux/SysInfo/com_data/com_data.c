#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/resource.h>
#include <sys/stat.h>


#include <string>
#include <vector>

#include <sys/sysinfo.h>

#include <sys/vfs.h>

#include "func.h"

using namespace std;

#define CPU_INFO "/tmp/cpu"
#define CPU_TEMP "/tmp/cpu_temp"

#define WIFI_STAT "/tmp/wifi_stat"
#define WIFI_DL "/tmp/wifi_dl"
#define WIFI_UL "/tmp/wifi_ul"

#define RAM_STAT "/tmp/ram_stat"
#define RAM_ALL "/tmp/ram_all"
#define RAM_USE "/tmp/ram_use"

#define HDD_STAT "/tmp/hdd_stat"
#define HDD_ALL "/tmp/hdd_all"
#define HDD_FREE "/tmp/hdd_free"

#define VOL "/tmp/vol_stat"


int f_cpu = 0;
int f_cpuTemp = 0;

int f_wifiStat = 0;
int f_wifiDl = 0;
int f_wifiUp = 0;

int f_ramStat = 0;
int f_ramAll = 0;
int f_ramUse = 0;

int f_hddStat = 0;
int f_hddAll = 0;
int f_hddFree = 0;

int f_vol = 0;

int f_port = 0;



void my_handler(int s){
    printf("Caught signal %d\n",s);

	if (f_cpu > 0) close(f_cpu);
	if (f_cpuTemp > 0) close(f_cpuTemp);

	if (f_wifiStat > 0) close(f_wifiStat);

	if (f_wifiDl > 0) close(f_wifiDl);

	if (f_wifiUp > 0) close(f_wifiUp);

	if (f_ramStat > 0) close(f_ramStat);

	if (f_ramAll > 0) close(f_ramAll);

	if (f_ramUse > 0) close(f_ramUse);

	if (f_hddStat > 0) close(f_hddStat);

	if (f_hddAll > 0) close(f_hddAll);

	if (f_hddFree > 0) close(f_hddFree);

	if (f_vol > 0) close(f_vol);

	if (f_port > 0) close(f_port);

    exit(1); 

}


// Protocol
// uint cpu_load; // 4 byte
// float cpu_temp; // 4 byte
// bool wifiStatus; // 1 byte
// char wifiDl[30]; // 30 byte
// char wifiUp[30]; // 30 byte
// uint ramStat; // 4 byte
// float ramAll; // 4 byte
// float ramUse; // 4 byte
// uint hddStat; // 4 byte
// float hddAll; // 4 byte
// float hddFree; // 4 byte
// uint vol; // 4 byte 


union _uData
{
	struct 
	{
		uint cpu_load; // 4 byte
		uint cpu_temp; // 4 byte
		bool wifiStatus; // 1 byte
		char wifiDl[30]; // 30 byte
		char wifiUp[30]; // 30 byte
		uint ramStat; // 4 byte
		float ramAll; // 4 byte
		float ramUse; // 4 byte
		char date[40];
		char time[40];
		uint hddStat; // 4 byte
		float hddAll; // 4 byte
		float hddFree; // 4 byte
		uint vol; // 4 byte 
	} data;
	char buf[180];
};

int main(int argc, char *argv[])
{
	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = my_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	sigaction(SIGINT, &sigIntHandler, NULL);

	string port = "";

	try
	{
		printf("%d\n", argc);
		if (argc <= 1) throw("Port unknown!");
		port = argv[1];

		printf("%s\n", port.c_str());
		f_port = open(port.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
		if (f_port < 0) throw("Open %s", port.c_str());

		
		
		
			
	
		
		
			
		f_ramAll = open(RAM_ALL, O_RDONLY );
		if (f_ramAll < 0) throw("File %s not open!", RAM_ALL );
			
		f_ramUse = open(RAM_USE, O_RDONLY );
		if (f_ramUse < 0) throw("File %s not open!", RAM_USE );

		f_hddStat = open(HDD_STAT, O_RDONLY );
		if (f_hddStat < 0) throw("File %s not open!", HDD_STAT );
		
		f_hddAll = open(HDD_ALL, O_RDONLY );
		if (f_hddAll < 0) throw("File %s not open!", HDD_ALL );
		
		f_hddFree = open(HDD_FREE, O_RDONLY );
		if (f_hddFree < 0) throw("File %s not open!", HDD_FREE );
		
		f_vol = open(VOL, O_RDONLY );
		if (f_vol < 0) throw("File %s not open!", VOL );

		_uData uData;

		uData.data.cpu_load = 0;
		uData.data.cpu_temp = 0;
		uData.data.wifiStatus = 0;
		memset(uData.data.wifiDl, 0, sizeof(uData.data.wifiDl));
		memset(uData.data.wifiUp, 0, sizeof(uData.data.wifiUp));
		uData.data.ramStat = 0;
		uData.data.ramAll = 0;
		uData.data.ramUse = 0;
		memset(uData.data.date, 0, sizeof(uData.data.date));
		memset(uData.data.time, 0, sizeof(uData.data.time));
		uData.data.hddStat = 0;
		uData.data.hddAll = 0;
		uData.data.hddFree = 0;
		uData.data.vol = 0;

		


		char buf[30];
		while (1)
		{
			f_cpu = open(CPU_INFO, O_RDONLY );
			if (f_cpu >= 0) 
			{
				memset(buf, 0, sizeof(buf));
				read(f_cpu, buf, sizeof(buf));
				uData.data.cpu_load = atoi(buf);
				//printf("cpuload %u\n", uData.data.cpu_load);
				close(f_cpu);
			}

			f_cpuTemp = open(CPU_TEMP, O_RDONLY );
			if (f_cpuTemp >= 0) 
			{
				memset(buf, 0, sizeof(buf));
				read(f_cpuTemp, buf, sizeof(buf));
				uData.data.cpu_temp = atoi(buf);
				//printf("cpu_temp %u\n", uData.data.cpu_temp);
				close(f_cpuTemp);
			}
			
			f_wifiStat = open(WIFI_STAT, O_RDONLY );
			if (f_wifiStat >= 0) 
			{
				memset(buf, 0, sizeof(buf));
				read(f_wifiStat, buf, sizeof(buf));
				uData.data.wifiStatus = atoi(buf);
				//printf("wifiStatus %u\n", uData.data.wifiStatus);
				close(f_wifiStat);
			}

			f_wifiDl = open(WIFI_DL, O_RDONLY );
			if (f_wifiDl >= 0)
			{
				memset(uData.data.wifiDl, 0, sizeof(uData.data.wifiDl));
				read(f_wifiDl, uData.data.wifiDl, sizeof(uData.data.wifiDl));
				//printf("wifiDl %s\n", uData.data.wifiDl);
				close(f_wifiDl);
			}

			f_wifiUp = open(WIFI_UL, O_RDONLY );
			if (f_wifiUp >= 0)
			{
				memset(uData.data.wifiUp, 0, sizeof(uData.data.wifiUp));
				read(f_wifiUp, uData.data.wifiUp, sizeof(uData.data.wifiUp));
				//printf("wifiUp %s\n", uData.data.wifiUp);
				close(f_wifiUp);
			}

			f_ramStat = open(RAM_STAT, O_RDONLY );
			if (f_ramStat >= 0) 
			{
				memset(buf, 0, sizeof(buf));
				read(f_ramStat, buf, sizeof(buf));
				uData.data.ramStat = atoi(buf);
				//printf("ramStat %u\n", uData.data.ramStat);
				close(f_ramStat);
			}

			f_ramAll = open(RAM_ALL, O_RDONLY );
			if (f_ramAll >= 0) 
			{
				memset(buf, 0, sizeof(buf));
				read(f_ramAll, buf, sizeof(buf));
				sscanf(buf, "%f", &uData.data.ramAll);
				//printf("ramAll %.2f\n", uData.data.ramAll);
				close(f_ramAll);
			}

			f_ramUse = open(RAM_USE, O_RDONLY );
			if (f_ramUse >= 0) 
			{
				memset(buf, 0, sizeof(buf));
				read(f_ramUse, buf, sizeof(buf));
				sscanf(buf, "%f", &uData.data.ramUse);
				//printf("ramUse %.2f\n", uData.data.ramUse);
				close(f_ramUse);
			}

			time_t t = time(NULL);
  			struct tm tm = *localtime(&t);
  			//printf("date: %02d/%02d/%04d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
			sprintf(uData.data.date, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
			
			//printf("time: %02d:%02d\n", tm.tm_hour, tm.tm_min);
			sprintf(uData.data.time, "%02d:%02d", tm.tm_hour, tm.tm_min);


			f_hddStat = open(HDD_STAT, O_RDONLY );
			if (f_hddStat >= 0) 
			{
				memset(buf, 0, sizeof(buf));
				read(f_hddStat, buf, sizeof(buf));
				uData.data.hddStat = atoi(buf);
				//printf("hddStat %u\n", uData.data.hddStat);
				close(f_hddStat);
			}

			f_hddAll = open(HDD_ALL, O_RDONLY );
			if (f_hddAll >= 0) 
			{
				memset(buf, 0, sizeof(buf));
				read(f_hddAll, buf, sizeof(buf));
				sscanf(buf, "%f", &uData.data.hddAll);
				//printf("hddAll %.0f\n", uData.data.hddAll);
				close(f_hddAll);
			}

			f_hddFree = open(HDD_FREE, O_RDONLY );
			if (f_hddFree >= 0) 
			{
				memset(buf, 0, sizeof(buf));
				read(f_hddFree, buf, sizeof(buf));
				sscanf(buf, "%f", &uData.data.hddFree);
				//printf("hddFree %.0f\n", uData.data.hddFree);
				close(f_hddFree);
			}

			f_vol = open(VOL, O_RDONLY );
			if (f_vol >= 0) 
			{
				memset(buf, 0, sizeof(buf));
				read(f_hddStat, buf, sizeof(buf));
				uData.data.vol = atoi(buf);
				//printf("vol %u\n", uData.data.vol);
				close(f_vol);
			}
			
			//for (int i = 0; i < sizeof(uData.buf); i++)
			//{
			//	printf("%02X ", uData.buf[i]);
			//}
			//printf("\n");	

			int bWrited = write(f_port, uData.buf, sizeof(uData.buf));
			if (bWrited < (int)sizeof(uData.buf)) throw("Write to port");

			usleep(500000);
		}

	}
	catch(const char* error_message)
	{
		if (f_cpu > 0) close(f_cpu);
		if (f_cpuTemp > 0) close(f_cpuTemp);

		if (f_wifiStat > 0) close(f_wifiStat);

		if (f_wifiDl > 0) close(f_wifiDl);

		if (f_wifiUp > 0) close(f_wifiUp);

		if (f_ramStat > 0) close(f_ramStat);

		if (f_ramAll > 0) close(f_ramAll);

		if (f_ramUse > 0) close(f_ramUse);

		if (f_hddStat > 0) close(f_hddStat);

		if (f_hddAll > 0) close(f_hddAll);

		if (f_hddFree > 0) close(f_hddFree);

		if (f_vol > 0) close(f_vol);

		if (f_port > 0) close(f_port);

		printf("Error: %s\n", error_message);
		return -1;

	}
	
	
    return 0;
}
