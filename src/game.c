#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include"../include/game.h"


int main(void)
{
	int rc;

	rc = set_term();
	if(rc < 1) {
		dbg("%s [DEBUG] %s [%d]: Unable to correctly set terminal\n", gettimestamp(), __FILE__, __LINE__);
	}
	dbg("%s [DEBUG] %s [%d]: Terminal environment set :)!\n", gettimestamp(), __FILE__, __LINE__);


	rc = start_game();
	dbg("%s [DEBUG] %s [%d]: Received return code of [%d]\n", gettimestamp(), __FILE__, __LINE__, rc);

	dbg("Exiting whole game\n");
	exit(EXIT_SUCCESS);
}//end main
