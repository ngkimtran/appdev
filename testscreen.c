//we test functions of screen.c
#include <stdio.h>
#include <unistd.h>
#include "screen.h"
#include "comm.h"
#include "sound.h"

int main(void) {
	//get posiion
	Position cur = getscreensize();
	char poststr[100];
	sprintf(poststr, "row=%d&col=%d", cur.row, cur.col);
	senddata(poststr, URL);
	gotoXY(1, 1);
	printf("Screen size, ROW = %d, COL = %d\n", cur.row, cur.col);
	printf("HTTP POST is sent to %s\n", URL);
	//printf("Press any key to clear the screen\n");
	getchar();
	getchar();
	int runtime = 500000;
	
	int i = 0;
	for(i = 0; i < cur.row; i++) {
		setcolors(YELLOW, RED);
		clearscreen();
		float step = (float)cur.col / cur.row;
		gotoXY(i+1, step*i+1);
		printf("Hello\n");
		usleep(runtime);
	}
	/*for(i = 0; i < 7; i++) {
		setcolors(YELLOW, RED);
		clearscreen();
		gotoXY(i+1, 80);
		printf("Hello\n");
		usleep(runtime);
	}
	for(i = 80; i > 0; i--) {
		setcolors(YELLOW, RED);
		clearscreen();
		gotoXY(7, i-1);
		printf("Hello\n");
		usleep(runtime);
	}
	for(i = 7; i > 0; i--) {
		setcolors(YELLOW, RED);
		clearscreen();
		gotoXY(i-1, 1);
		printf("Hello\n");
		usleep(runtime);
	}
	*/

	//Homwork
	for(int i = 0; i < 20; i++) {
		clearscreen();

		setfgcolor(GREEN);
		gotoXY(i+1, 2*i+1);
#ifdef UNICODE
		printf("%s", BOX);
		printf("%s", BOX);
		printf("%s", BOX);
		printf("%s", BOX);
#else
		printf("%c", '#');
		printf("%c", '#');
		printf("%c", '#');
		printf("%c", '#');
#endif

		setfgcolor(RED);
		gotoXY(20-i, 2*i);
		printf("HELLO\n");

		usleep(runtime);
	}

	for(int i = 0; i < 20; i++) {
		clearscreen();

		setfgcolor(GREEN);
		gotoXY(20-i, 40+(2*i+1));
#ifdef UNICODE
		printf("%s", BOX);
		printf("%s", BOX);
		printf("%s", BOX);
		printf("%s", BOX);
#else
		printf("%c", '#');
		printf("%c", '#');
		printf("%c", '#');
		printf("%c", '#');
#endif

		setfgcolor(RED);
		gotoXY(i+1, 40+2*i);
		printf("HELLO\n");

		usleep(runtime);
	}

	//printf("The following message will be in YELLOW color\n");
	gotoXY(14, 35);
	setfgcolor(MAGENTA);
	printf("e1900309\n");
	//getchar();
	drawbar(30, 30);
	drawbar(50, 30);

	getchar();
	resetcolor();
	clearscreen();
	printf("\nThis line is back to default color\n");


	//read .WAV file
	FILE *fp;
	fp = fopen("1.wav", "r");
	WAVheader h = readwavhdr(fp);
	fclose(fp);

	displaywavhdr(h);




	return 0;
}
