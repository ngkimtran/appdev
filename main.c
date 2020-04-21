//we test functions of screen.c
#include <stdio.h>
#include <unistd.h>
#include "screen.h"
#include "comm.h"
#include "sound.h"

int main(void) {
	FILE *fp;
	fp = fopen("1.wav", "r");

	WAVheader h = readwavhdr(fp);
	displaywavhdr(h);

	clearscreen();
	wavdata(h, fp);

	getchar();
	fclose(fp);

	return 0;
}
