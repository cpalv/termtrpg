#include<stdlib.h>
#include<stdio.h>
#include<termios.h>
#include<unistd.h>
#include"../include/game.h"

#define START_NEW 0
#define LOAD_GAME 1

const char *opts[2] = {"Start New Game\n", "Load Game\n"};
static struct termios *orig;	// Original terminal structure to revert changes

static void print_main_menu(int opt) {

		switch(opt){
			case 0:
				printf("\033[H\033[2J\033(B\033[m");
//		printf("Highlighted = [%d]\n", highlighted);
				printf("\tGAME\n");
				printf("\tSelect an option or press CTRL+D to exit :)\n\n");
				printf("\033[0;30;47m\t\t%s\033(B\033[m", opts[0]);
				printf("\t\t%s", opts[1]);
				break;
			case 1:
				printf("\033[H\033[2J\033(B\033[m");
//		printf("Highlighted = [%d]\n", highlighted);
				printf("\tGAME\n");
				printf("\tSelect an option or press CTRL+D to exit :)\n\n");
				printf("\t\t%s", opts[0]);
				printf("\033[0;30;47m\t\t%s\033(B\033[m", opts[1]);
				break;
		}//end switch

}//end function

/* * * PUBLIC FUNCTIONS * * */

int set_term()
{
	int rc;
	struct termios *tmp;
	const struct termios *game_term;

	orig = (struct termios *) calloc(1, sizeof(struct termios));
	
	rc = tcgetattr(STDIN_FILENO, orig);
	if(rc) {
		dbg("Couldn't get terminalio attributes\n");
		return -1;
	}

	tmp = orig;
	tmp->c_lflag &= ~(ICANON);	// bitwise and with complement of ICANON setting, to unset default ICANON
								// man 3 termios
								// In noncanonical mode input is available immediately
								// ie, user doesn't have to type a line-delimiter

	game_term = tmp;

	rc = tcsetattr(STDIN_FILENO, TCSANOW, game_term);
	if(rc) {
		dbg("Failed to set TCSANOW flag\n");
		return -1;
	}
		
	return 1;
}

/*
 * TODO: Fix double entering arrow keys problem
 *
 * Problem:
 * 		When entering arrow keys at least twice
 *		...(possibly occurs for any keyboard input)...
 *		while loop is exited
 * 
 * Expected Behavior:
 *		If more than one character/sequence is entered 
 *		We'd like to ignore input
 *		More ideally, we'd listen to each keystork individually (Async IO?)
 */
int start_game(void)
{
	int highlighted = 0;
	char c;

	print_main_menu(START_NEW);

	while(( c = getchar()) != EOF) {
		// Escape sequence for arrow keys looks like the following
		// "\033[A"
		if( c == '\033'){
			getchar();//skip [
			switch(getchar()) {
				case 'A':
					//up arrow
					dbg( "%s [DEBUG] %s [%d]: Up arrow pressed\n", gettimestamp(), __FILE__, __LINE__);
					highlighted--;
					if(highlighted < 0)
						highlighted = 1;
					break;
				case 'B':
					//down arrow key
					dbg( "%s [DEBUG] %s [%d]: Down arrow pressed\n", gettimestamp(), __FILE__, __LINE__);
					highlighted++;
					if(highlighted > 1)
						highlighted = 0;
					break;
/*				
 * Right and left arrows not needed at this moment
 *				case 'C':
 *					//right arrow key
 *					printf("Right arrow pressed\n");
 *					break;
 *				case 'D':
 *					//left arrow key
 *					printf("Left arrow pressed\n");
 *					break;
 */
				default:
					break;
			}//end switch
	//		getchar();//skip last newline

		} else if( c != '\n') {
			// If person did not ONLY hit enter
			// retrieve remainder of stdin stream
			char tmp;
			while(( tmp = getchar()) != '\n')
				break;

		} else if( c == '\n') {
			// I think we only hit enter
			// GTFO
			break;
		}//end if

	print_main_menu(highlighted);
	}//end while

	//return the option selected code
	dbg( "%s [DEBUG] %s [%d]: sending [%d] up to main :)\n", gettimestamp(), __FILE__, __LINE__, highlighted);
	return highlighted;
}//end main
