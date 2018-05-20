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
	printf("Received return code of [%d]\n", rc);

	printf("Exiting whole game\n");
	exit(EXIT_SUCCESS);
}//end main
