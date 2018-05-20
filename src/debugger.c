#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#define LOG_FILE "../log/game_log.txt"
#define BUFFSZ 128



void dbg(const char * msg, ...)
{
	char buff[BUFFSZ] = {'\0'};
	va_list args;
	int n = 0, fd;

	
	va_start(args, msg);
	fd = open(LOG_FILE, O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0644);
	vsnprintf( buff, BUFFSZ, msg, args);
	va_end(args);

	n = strlen(buff);
	n = write( fd, buff, n);
	//printf("Wrote %d of %s", n , buff);
	//sleep(10);
}
