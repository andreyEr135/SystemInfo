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

using namespace std;

typedef struct { unsigned long total; unsigned long work; } Tcoredata;
typedef struct { Tcoredata data[2]; float usage; } Tcore;
typedef std::vector< Tcore > Tcores;

Tcores   cpu;

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
	int j = 0;
	while (j < 2)
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
		j++;
		sleep(1);
	}
	printf( "%3.0f\n", cpu[0].usage );
}

void getMemLoad()
{
	struct sysinfo info;
	sysinfo( &info );
	uint total = ( ( info.totalram >> 10 ) * info.mem_unit ) >> 10;
	uint free = ( ( info.freeram >> 10 ) * info.mem_unit ) >> 10;
	uint use = total - free;
	uint usePrcnt = (use*100)/total;
	float total_f = (float)total/1024;
	float use_f = (float)use/1024;
	printf("%.02f %.02f %u\n", total_f, use_f, usePrcnt);
}

/**
 * get_fs_size - Определяет размер ФС.
 * @param anyfile Путь к любому файлу на этой ФС.
 * @return Размер ФС в блоках.
 */
long get_fs_size(const char *anyfile)
{
  struct statfs buf;
  statfs(anyfile, &buf);
  struct stat st;
  stat(anyfile, &st);
  return buf.f_blocks * st.st_blksize/1024/1024/1024;
}

/**
 * get_fs_free - Определяет свободное место на ФС.
 * @param anyfile Путь к любому файлу на этой ФС.
 * @return Размер ФС в блоках.
 */
long get_fs_free(const char *anyfile)
{
  struct statfs buf;
  statfs(anyfile, &buf);
  struct stat st;
  stat(anyfile, &st);
  
  return buf.f_bfree * st.st_blksize/1024/1024/1024;
}


void getHddInfo()
{
	long allSize = get_fs_size("/");
		
	long freeSpace = get_fs_free("/");
	printf("%lu %lu\n", allSize, freeSpace);

}



int main(int argc, char *argv[])
{
	if (strstr(argv[1],"cpu") != 0) getCpuLoad();
	else if (strstr(argv[1],"mem") != 0) getMemLoad();
	else if (strstr(argv[1],"hdd") != 0) getHddInfo();
	
	
    	return 0;
}
