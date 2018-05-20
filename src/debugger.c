#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#define LOG_FILE "../log/game_log.txt"
#define BUFFSZ 128



void dbg(const char * file, int line, const char * msg)
{
	char buff[BUFFSZ] = {'\0'};
	int n = 0, fd;

	//fd = open(LOG_FILE, O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0644);
	snprintf( buff, BUFFSZ, "%s [%d]: %s\n", file, line, msg);
	n = strlen(buff);
	n = write( lfd, buff, n);
	//printf("Wrote %d of %s", n , buff);
	//sleep(10);
}
