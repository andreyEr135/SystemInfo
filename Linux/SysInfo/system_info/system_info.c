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

typedef struct { unsigned long total; unsigned long work; } Tcoredata;
typedef struct { Tcoredata data[2]; float usage; } Tcore;
typedef std::vector< Tcore > Tcores;

Tcores   cpu;

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


#define TEMP_STR "/sys/class/thermal/thermal_zone0/temp"
#define WIFI "wlp4s0"



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




bool getcpustat( )
{
	FILE* fp = NULL;
	
	if( ( fp = fopen( "/proc/stat", "r" ) ) == NULL ) return false;
	char buf[ 256 ];
	unsigned long v[ 7 ];
	while( !feof( fp ) )
	{
		if( !fgets( buf, sizeof(buf), fp ) ) break;
		if( strncmp( buf, "cpu", 3 ) != 0 ) continue;
		sscanf( buf+5, "%lu %lu %lu %lu %lu %lu %lu", &v[0],&v[1],&v[2],&v[3],&v[4],&v[5],&v[6] );
			
		Tcoredata d = {0,0};
		for( int i = 0; i < 7; i++ ) d.total += v[ i ];
		//for( int i = 0; i < 3; i++ ) d.work  += v[ i ];
		//d.work = d.total - v[3] - v[4];
		d.work = d.total - v[3];
			
		uint i;
		if( buf[3] == ' ' ) i = 0;
		else { sscanf( buf+3, "%u", &i ); i++; }
		if( i >= cpu.size() ) cpu.resize( i+1 );
		cpu[ i ].data[ 0 ] = d;
	}
	fclose( fp );	
	return true;
}

void getCpuLoad()
{
	
	for( size_t i = 0; i < cpu.size(); i++ ) cpu[ i ].data[ 1 ] = cpu[ i ].data[ 0 ];
	getcpustat( );

	for( size_t i = 0; i < cpu.size(); i++ )
	{
		unsigned long dtotal = cpu[ i ].data[0].total - cpu[ i ].data[1].total;
		unsigned long dwork  = cpu[ i ].data[0].work  - cpu[ i ].data[1].work;
		if( dtotal == 0 ) cpu[ i ].usage = 0.0;
		else cpu[ i ].usage = double( 100.0 ) * dwork / dtotal;
		//printf( "cpu%d %3.0f\n", i, cpu[i].usage );
	}
	char buf[20];
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%.0f", cpu[0].usage);
	lseek(f_cpu, SEEK_SET, 0);
	write(f_cpu, buf, sizeof(buf));
}


void getMemInfo()
{
	uint freeMem = 0;
	uint allMem = 0;
	uint useMem = 0;
	uint prcnt = 0;
	Tstrlist outData;
	GetProcessData( "free", outData, 1000 );
	string res = "";
	if (outData.size() == 0)
	{
		return;
	}
	res = outData[1];

	if (res.find("Память:") < 0) return;
	res = res.substr(res.find("Память:") + 13);
	sscanf(res.c_str(), "%u %u", &allMem, &useMem);
	
	freeMem = allMem - useMem;
	prcnt = ((float)useMem / (float)allMem) * 100;
	


	float useMemory = (float) useMem;
	useMemory = useMemory / 1024 / 1024;
	float allMemory = (float) allMem;
	allMemory = allMemory / 1024 / 1024;

	char buf[64];
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%.2f", allMemory);
	lseek(f_ramAll, SEEK_SET, 0);
	write(f_ramAll, buf, sizeof(buf));

	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%.2f", useMemory);
	lseek(f_ramUse, SEEK_SET, 0);
	write(f_ramUse, buf, sizeof(buf));

	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%u", prcnt);
	lseek(f_ramStat, SEEK_SET, 0);
	write(f_ramStat, buf, sizeof(buf));

}

void getHddInfo()
{
	uint allMem = 0;
	uint freeMem = 0;
	uint useMem = 0;
	uint prcnt = 0;
	Tstrlist outData;
	GetProcessData( "df -h '/", outData, 1000 );
	string res = "";
	if (outData.size() == 0)
	{
		return;
	}
	res = outData[1];

	char blockDev[40];
	char allStr[10];
	char useStr[10];
	char freeStr[10];
	char prcntStr[10];

	sscanf(res.c_str(), "%s %s %s %s %s", &blockDev, &allStr, &useStr, &freeStr, &prcntStr);
	
	allStr[strlen(allStr) - 1] = 0;
	useStr[strlen(useStr) - 1] = 0;
	freeStr[strlen(freeStr) - 1] = 0;
	prcntStr[strlen(prcntStr) - 1] = 0;

	allMem = atoi(allStr);
	freeMem = atoi(freeStr);
	useMem = atoi(useStr);
	prcnt = atoi(prcntStr);

	char buf[64];
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%u", allMem);
	lseek(f_hddAll, SEEK_SET, 0);
	write(f_hddAll, buf, sizeof(buf));

	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%u", freeMem);
	lseek(f_hddFree, SEEK_SET, 0);
	write(f_hddFree, buf, sizeof(buf));

	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%u", prcnt);
	lseek(f_hddStat, SEEK_SET, 0);
	write(f_hddStat, buf, sizeof(buf));

}

void getCpuTemp()
{
	int fileTemp = open(TEMP_STR, O_RDONLY);
	if (fileTemp < 0) return;
	float t = 0;
	char buf[10];
	memset(buf, 0, sizeof(buf));
	read(fileTemp, buf, sizeof(buf));
	close(fileTemp);
	sscanf(buf, "%f", &t);
	t = t/1000;

	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%.0f", t);
	lseek(f_cpuTemp, SEEK_SET, 0);
	write(f_cpuTemp, buf, sizeof(buf));
}

void getVolumeInfo()
{
	uint volume = 0;

	Tstrlist outData;
	GetProcessData( "amixer -c 1 -M -D pulse get Master", outData, 1000 );
	string res = "";
	if (outData.size() == 0)
	{
		return;
	}
	for (int i = 0; i < outData.size(); i++)
	{
		res = outData[i];
		if ((int)(res.find("Front Left:")) > 0) break;
	}

	if ((int)res.find('%%') < 0) return;

	int id_end = res.find('%%');
	int id_beg = id_end;
	
	while (id_beg > 0)
	{
		if (res[id_beg] == '[') break;
		id_beg--;
	}
	id_beg = id_beg + 1;
	res = res.substr(id_beg, id_end-id_beg);
	volume = atoi(res.c_str());


	char buf[10];
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%u", volume);
	lseek(f_vol, SEEK_SET, 0);
	write(f_vol, buf, sizeof(buf));
}

void getWifiInfo()
{
	string Ul = "";
	string Dl = "";
	bool status = false;

	Tstrlist outData;
	GetProcessData( "ip a", outData, 1000 );
	string res = "";
	if (outData.size() == 0)
	{
		return;
	}

	for (int i = 0; i < outData.size(); i++)
	{
		if ((int)outData[i].find(WIFI) > 0) 
		{
			res = outData[i];
			break;
		}
	}
	if (res == "") return;

	if ((int)res.find("state UP") > 0) status = true;
	else status = false;

	if (status)
	{
		Tstrlist infoWifi;
		if (!readfiletext( "/tmp/wifi.log", infoWifi )) return;
		res = infoWifi[infoWifi.size()-1];
		if ((int)res.find("\"rx\":{\"ratestring\"") < 0) return;
		int id_beg = (int)res.find("\"rx\":{\"ratestring\"") + 20;
		res = res.substr(id_beg);
		int id_end = res.find('\"');
		Ul = res.substr(0, id_end);

		if ((int)res.find("\"tx\":{\"ratestring\"") < 0) return;
		id_beg = (int)res.find("\"tx\":{\"ratestring\"") + 20;
		res = res.substr(id_beg);
		id_end = res.find('\"');
		Dl = res.substr(0, id_end);
	} else
	{
		Ul = "0";
		Dl = "0";
	}	
	Ul = ratestr(Ul);
	Dl = ratestr(Dl);

	char buf[30];
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%d", status);
	lseek(f_wifiStat, SEEK_SET, 0);
	write(f_wifiStat, buf, sizeof(buf));

	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%s", Dl.c_str());
	lseek(f_wifiDl, SEEK_SET, 0);
	write(f_wifiDl, buf, sizeof(buf));

	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%s", Ul.c_str());
	lseek(f_wifiUp, SEEK_SET, 0);
	write(f_wifiUp, buf, sizeof(buf));


}


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

    exit(1); 

}


int main(int argc, char *argv[])
{
	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = my_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	sigaction(SIGINT, &sigIntHandler, NULL);

	try
	{
		remove(CPU_INFO);
		remove(CPU_TEMP);
		remove(WIFI_STAT);
		remove(WIFI_DL);
		remove(WIFI_UL);
		remove(RAM_STAT);
		remove(RAM_ALL);
		remove(RAM_USE);
		remove(HDD_STAT);
		remove(HDD_ALL);
		remove(HDD_FREE);
		remove(VOL);



		f_cpu = open(CPU_INFO, O_RDWR | O_SYNC | O_CREAT, S_IRUSR );
		if (f_cpu < 0) throw("File %s not open!", CPU_INFO );
		
		f_cpuTemp = open(CPU_TEMP, O_RDWR | O_SYNC | O_CREAT, S_IRUSR );
		if (f_cpuTemp < 0) throw("File %s not open!", CPU_TEMP );
			
		f_wifiStat = open(WIFI_STAT, O_RDWR | O_SYNC | O_CREAT, S_IRUSR );
		if (f_wifiStat < 0) throw("File %s not open!", WIFI_STAT );
			
		f_wifiDl = open(WIFI_DL, O_RDWR | O_SYNC  | O_CREAT, S_IRUSR  );
		if (f_wifiDl < 0) throw("File %s not open!", WIFI_DL );
			
		f_wifiUp = open(WIFI_UL, O_RDWR | O_SYNC | O_CREAT, S_IRUSR  );
		if (f_wifiUp < 0) throw("File %s not open!", WIFI_UL );

		f_ramStat = open(RAM_STAT, O_RDWR | O_SYNC | O_CREAT, S_IRUSR  );
		if (f_ramStat < 0) throw("File %s not open!", RAM_STAT );
			
		f_ramAll = open(RAM_ALL, O_RDWR | O_SYNC | O_CREAT, S_IRUSR  );
		if (f_ramAll < 0) throw("File %s not open!", RAM_ALL );
			
		f_ramUse = open(RAM_USE, O_RDWR | O_SYNC | O_CREAT, S_IRUSR  );
		if (f_ramUse < 0) throw("File %s not open!", RAM_USE );

		f_hddStat = open(HDD_STAT, O_RDWR | O_SYNC | O_CREAT, S_IRUSR  );
		if (f_hddStat < 0) throw("File %s not open!", HDD_STAT );
		
		f_hddAll = open(HDD_ALL, O_RDWR | O_SYNC | O_CREAT, S_IRUSR  );
		if (f_hddAll < 0) throw("File %s not open!", HDD_ALL );
		
		f_hddFree = open(HDD_FREE, O_RDWR | O_SYNC | O_CREAT, S_IRUSR  );
		if (f_hddFree < 0) throw("File %s not open!", HDD_FREE );
		
		f_vol = open(VOL, O_CREAT | O_RDWR | O_SYNC | O_CREAT, S_IRUSR );
		if (f_vol < 0) throw("File %s not open!", VOL );


		
		while (1)
		{
			getCpuLoad();
			getMemInfo();
			getHddInfo();
			getCpuTemp();
			getVolumeInfo();
			getWifiInfo();
			

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

		printf("Error: %s\n", error_message);
		return -1;



	}

	



	//if (strstr(argv[1],"cpu") != 0) getCpuLoad();
	//else if (strstr(argv[1],"mem") != 0) getMemLoad();
	//else if (strstr(argv[1],"hdd") != 0) getHddInfo();
	
	
    return 0;
}
