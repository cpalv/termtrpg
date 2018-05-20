#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<dirent.h>

struct boardspace {
	char * sp;
};

struct character {
	double hp;
};

int main(int argc, char * argv[])
{
	struct boardspace * brd = malloc(sizeof(struct boardspace));
	brd->sp = "hello structs";

	struct boardspace * brd2 = malloc(sizeof(struct boardspace));

	struct character * newchar = malloc(sizeof(struct character));
	newchar->hp = 10;

	FILE * gfile;

	DIR * gdir;
	struct dirent * entries[15];

	size_t bytesw, bytesr;

	int rc, i;

	printf(" ----\n");
	printf("|    |\n");
	printf(" ----\n");

	/* Check if game file exists
	 * if it does not exist create file
	 * otherwise open existing file */
	if ( access("/home/ealvarado/test/gtest", F_OK) ) {
		gfile = fopen("/home/ealvarado/test/gtest", "w+");	
		printf("Created or truncated game file\n");
	} else {
		gfile = fopen("/home/ealvarado/test/gtest", "r+");
		printf("Opened existing game file\n");
	}	
	
	/* Save and read game */
	bytesw = fwrite((void *) brd, sizeof(brd), 1, gfile);
	printf("Bytes written = %ld\n", bytesw);

	fseek(gfile, 0L, SEEK_SET);

	bytesr = fread((void *) brd2, sizeof(brd2), 1, gfile);	
	printf("Bytes read = %ld\nbrd2->sp = [%s]\n", bytesr, brd2->sp);

	/* Open and scan game directory for saved files */
	gdir = opendir("/home/ealvarado/test/");
	if(!gdir){
		perror("Couldn't open dir");
	} else {
		printf("Dir open\n");
	}

	i = 0;	
	while( ( entries[i] = readdir(gdir))) {
		printf("Dir entry %d = [%s]\n", i, entries[i]->d_name);
		i++;
	}

	printf("This is entry 2: [%s]\n",entries[1]->d_name);

	exit(0);
}
