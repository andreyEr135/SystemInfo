#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <inttypes.h>
#include <dirent.h>
#include <stdlib.h>
#include <fcntl.h>

#include <unistd.h>

#include <sys/prctl.h>
#include <sys/wait.h>

#include <string>
#include <vector>

#define xfclose(a) do{ if(a) fclose(a); a=NULL; }while(0)


typedef std::vector< std::string > Tstrlist;
typedef Tstrlist::iterator TstrlistIt;

int GetProcessData( std::string command, Tstrlist &data, int timeout );
bool readfiletext( std::string filename, Tstrlist& text );
std::string ratestr(std::string input);


#endif