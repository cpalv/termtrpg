#include<stdlib.h>
#include<stdio.h>
#include"../include/game.h"

#define START_NEW 0
#define LOAD_GAME 1

const char * opts[2] = {"Start New Game\n", "Load Game\n"};

void print_main_menu(int opt) {

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
					dbg( __FILE__, __LINE__, "Up arrow pressed");
					highlighted--;
					if(highlighted < 0)
						highlighted = 1;
					break;
				case 'B':
					//down arrow key
					dbg(__FILE__, __LINE__, "Down arrow pressed");
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
			getchar();//skip last newline

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
	dbg( __FILE__, __LINE__, "Exiting start function\n");
	dbg( __FILE__, __LINE__, "sending [%d] up to main :)\n", highlighted);
	return highlighted;
}//end main
