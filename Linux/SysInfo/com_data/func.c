#include "func.h"

using namespace std;

bool RunProcess( pid_t& pid, const char* command, int* inpipe, int* outpipe )
{
	//pthread_mutex_lock( &processmutex );
	bool result = false;

	int checkpipe[2];
	//if( pipe2( checkpipe, O_CLOEXEC ) != 0 ) printf( "Error: create checkpipe\n" );

	if( pipe( checkpipe ) != 0 ) printf( "Error: create checkpipe\n" );
	int rc;
	if( ( rc = fcntl( checkpipe[1], F_GETFD, 0 ) ) < 0 || fcntl( checkpipe[1], F_SETFD, rc | FD_CLOEXEC ) == -1
	 || ( rc = fcntl( checkpipe[0], F_GETFD, 0 ) ) < 0 || fcntl( checkpipe[0], F_SETFD, rc | FD_CLOEXEC ) == -1 ) printf( "Error: checkpipe FD_CLOEXEC\n" );


	pid = fork( );
	if( pid == -1 )
	{
		printf( "Error: fork\n" );
		result = false;
	}
	else
	if ( pid == 0 ) // для дочернего процесса
	{
		close( checkpipe[0] ); // close checkpipe read

		if( inpipe )
		{
			if( dup2( inpipe[1], STDOUT_FILENO ) == -1 ) printf( "Error: dup2 STDOUT\n" ); // child stdout --> parent inpipe
			if( dup2( inpipe[1], STDERR_FILENO ) == -1 ) printf( "Error: dup2 STDERR\n" ); // child stderr --> parent inpipe
			if( close( inpipe[0] ) != 0 ) printf( "Error: close child inpipe[0]\n" );
			if( close( inpipe[1] ) != 0 ) printf( "Error: close child inpipe[1]\n" );
		}
		if( outpipe )
		{
			if( dup2( outpipe[0], STDIN_FILENO ) == -1 ) printf( "Error: dup2 STDIN\n" ); // parent outpipe --> child stdin
			if( close( outpipe[0] ) != 0 ) printf( "Error: close child outpipe[0]\n" );
			if( close( outpipe[1] ) != 0 ) printf( "Error: close child outpipe[1]\n" );
		}
		// close all fds, кроме 0 1 2 and checkpipe[1]
		long max = sysconf( _SC_OPEN_MAX );
		while( --max > 2 ) if( max != checkpipe[1] ) close( max );
		errno = 0;

		//разблокировка всех сигналов
		sigset_t sig_mask;
		sigfillset( &sig_mask );
		sigprocmask( SIG_UNBLOCK, &sig_mask, NULL );

		//сигнал, приходящий процессу при завершении работы родительского процесса
		prctl( PR_SET_PDEATHSIG, SIGTERM );

		int size = strlen(command) + 1;
		char buf[ size ]; strcpy( buf, command );
		char* arg[64]; memset( arg, 0, sizeof(arg) );
		int n = 0; bool vl = false, st = false;
		for( int i = 0; i < size; i++ )
		{

			if( isspace( buf[i] ) && !st ) { buf[i] = 0; vl = false; continue; }
			if( ( buf[i] == '\'' )||( buf[i] == '\"' ) ) { st = !st; buf[i] = 0; continue; }
			if( !vl ) { arg[ n++ ] = buf + i; vl = true; }
		}

		//string s; for( int i = 0; i < 64; i++ ) { if( !arg[i] ) break; s += string("[") + arg[i] + "]"; } printf( "%s\n", s.c_str() );

		//setenv( "LD_PRELOAD", "/opt/TestStudio3/bin/libdxnobuf.so", 1 );
		//setenv( "LD_PRELOAD", "libdxnobuf.so", 1 );

		execvp( arg[0], arg );

		printf( "Error: execvp '%s'\n", arg[0] );
		if( write( checkpipe[1], "X", 1 ) == -1 ) printf( "Error: write checkpipe\n" );
		close( checkpipe[1] );

		_exit( EXIT_FAILURE );
	}
	else  // родительский процесс
	{
		close( checkpipe[1] );  // close checkpipe write

		char out; int n = read( checkpipe[0], &out, 1 );
		close( checkpipe[0] );
		result = ( n == 0 );
	}

	//if( !result ) Error( "run '%s' fault, pid=%d\n", command, pid );
	//pthread_mutex_unlock( &processmutex );
	return result;
}
//-------------------------------------------------------------



pid_t RunProcessIO( const char* command, FILE* &instream, FILE* &outstream )
{
	//pthread_mutex_lock( &processiomutex );
	int inpipe[2];   if( pipe( inpipe  ) != 0 ) { printf( "create inpipe\n" ); return 0; }
	int outpipe[2];  if( pipe( outpipe ) != 0 ) { printf( "create outpipe\n" ); return 0; }

	pid_t childpid = 0;
	if( RunProcess( childpid, command, inpipe, outpipe ) )
	{
		int flags = 0;
		if( ( flags = fcntl( inpipe [0], F_GETFD, 0 ) ) < 0 || fcntl( inpipe [0], F_SETFD, flags | FD_CLOEXEC ) == -1 ) { printf( "inpipe[0] FD_CLOEXEC" ); return 0; }
		if( ( flags = fcntl( outpipe[1], F_GETFD, 0 ) ) < 0 || fcntl( outpipe[1], F_SETFD, flags | FD_CLOEXEC ) == -1 ) { printf( "outpipe[1] FD_CLOEXEC" ); return 0; }

		if( !( instream  = fdopen( inpipe [0], "r" ) ) ) 
        {
            printf( "create instream\n" );  // чтение из inpipe
            return 0; 
        }
		if( !( outstream = fdopen( outpipe[1], "w" ) ) ) 
        {
            printf( "create outstream\n" ); // запись в outpipe
            return 0; 
        }

		errno = 0;
		if( instream )  setvbuf( instream,  NULL, _IONBF, 0 );
		if( outstream ) setvbuf( outstream, NULL, _IONBF, 0 );
	}
	else
	{
		instream = NULL;
		outstream = NULL;
		close( inpipe [0] );
		close( outpipe[1] );
	}
	close( inpipe [1] );  // закрываем запись в inpipe
	close( outpipe[0] );  // закрываем чтение из outpipe
	//pthread_mutex_unlock( &processiomutex );
	return childpid;
}


int WaitProcess( const pid_t pid )
{
	int status = 0;
	waitpid( pid, &status, 0 );
	return status;
}

//-------------------------------------------------------------

int WaitProcessIO( pid_t pid, FILE* &instream, FILE* &outstream )
{
	int status = WaitProcess( pid );
	xfclose( instream );
	xfclose( outstream );
	return status;
}


int GetProcessData( std::string command, Tstrlist &data, int timeout )
{
	FILE *instream, *outstream;
	pid_t childpid = RunProcessIO( command.c_str(), instream, outstream );
	if( !instream ) return WaitProcessIO( childpid, instream, outstream );

	//if( setpriority( PRIO_PROCESS, childpid, -19 ) == -1 ) Error( "setpriority\n" );

	if( timeout != 0 )
	{
		fd_set readfds;
		FD_ZERO( &readfds );
		FD_SET( fileno(instream), &readfds );
		struct timeval to;
		timeout *= 1000;
		to.tv_sec = timeout / 1000000;
		to.tv_usec = timeout % 1000000;
		int selectresult = select( fileno(instream) + 1, &readfds, 0, 0, &to );
		if( selectresult < 0  ) { printf( "process '%s' select error, killing process...\n", command.c_str() ); return -1; }
		if( selectresult == 0 ) { printf( "process '%s' TIMEOUT, killing process...\n", command.c_str() ); return -1; }
		if( selectresult <= 0 )
			if( kill( childpid, SIGTERM ) !=0 ) { printf( "kill %d SIGTERM\n", childpid );  return -1; }
	}

	char buf[ 1024 ];
	while( !feof( instream ) )
	{
		if( !fgets( buf, sizeof(buf), instream ) ) break;
		data.push_back( string( buf ) );
	}

	int result = WaitProcessIO( childpid, instream, outstream );

	//if( WIFSIGNALED(result) )
	//	if( WTERMSIG(result) == SIGTERM ) Error( "process '%s' pid[%d] timeout\n", command.c_str(), childpid );
	return result;
}


bool readfiletext( std::string filename, Tstrlist& text )
{
	text.clear();
	if( filename.empty() ) return false;
	char buf[1024]; *buf = 0;
	FILE* fp = fopen( filename.c_str(), "r" );
	if( !fp ) { errno = 0; return false; }
	while( fgets( buf, sizeof(buf), fp ) ) text.push_back( buf );
	xfclose( fp );
	errno = 0;
	return true;
}

std::string ratestr(std::string input)
{
    string out = input;
    int id = out.find("mbit/s");
    if (id >= 0)
    {
        out = out.substr(0, id - 1);
        out = out + "mb/s";
        return out;
    } else
    {
        id = out.find("kbit/s");
        if (id >= 0)
        {
            out = out.substr(0, id - 1);
            out = out + "kb/s";
            return out;
        } else
        {
            id = out.find("bit/s");
            if (id >= 0)
            {
                out = out.substr(0, id - 1);
                out = out + "b/s";
                return out;
            }
        }
    }
    return out;
}