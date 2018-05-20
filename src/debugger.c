#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#define LOG_FILE "../log/game_log.txt"
#define BUFFSZ 128


/*
 * TODO: fix log file being continously truncated
 *
 * Expected Behavior:
 *		Truncate file at initial open
 *		append all future writes
 *		possibly need to make a global file descriptor
 *
 * TODO: Add time stamp to log file
 */
void dbg(const char * msg, ...)
{
	char buff[BUFFSZ] = {'\0'};
	va_list args;
	int n = 0, bytesw = 0, fd;

	
	va_start(args, msg);
	fd = open(LOG_FILE, O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0644);
	vsnprintf( buff, BUFFSZ, msg, args);
	va_end(args);

	n = strlen(buff);
	bytesw = write( fd, buff, n);
	if( bytesw < n)
		write( fd, "Incomplete Write to Log!\n", 26);	// > echo "words" | wc -c 
														// already includes '\n' in count
}
