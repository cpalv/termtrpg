#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include"../include/game.h"


int main(void)
{
	int rc;

	rc = start_game();
	dbg("DEBUG %s [%d]: Received return code of [%d]\n", __FILE__, __LINE__, rc);

	dbg("Exiting whole game\n");
	exit(EXIT_SUCCESS);
}//end main
