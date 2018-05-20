#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

#define LOG_FILE "../log/game_log.txt"
#define BUFFSZ 128
#define TSTMPSZ 9 //TimeSTaMP SiZe

static int dbging = 0;
static int LOG;

static void dbginit()
{
	if(dbging) {
		// We've already opened our log file
	} else {
		LOG = open( LOG_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
		dbging = 1;
	}//end if
}//end function

/* * * PUBLIC FUNCTIONS * * */

char * gettimestamp()
{
	const struct tm * time_info;
	time_t rawtime;
	char * timestamp;

	timestamp = (char *) calloc(TSTMPSZ, sizeof(char));
	if(!timestamp)
		return NULL;

	time( &rawtime);
	time_info = localtime(&rawtime);
	strftime(timestamp, TSTMPSZ, "%H:%M:%S", time_info);

	return (timestamp);
}//end function

void dbg(const char * msg, ...)
{
	char buff[BUFFSZ] = {'\0'};
	va_list args;
	int n = 0, bytesw = 0;
	
	dbginit();
	
	va_start(args, msg);
	vsnprintf( buff, BUFFSZ, msg, args);
	va_end(args);

	n = strlen(buff);
	bytesw = write( LOG, buff, n);
	if( bytesw < n)
		write( LOG, "Incomplete Write to Log!\n", 26);	// > echo "words" | wc -c 
														// already includes '\n' in count
}//end function
