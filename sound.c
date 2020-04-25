#include <stdio.h>
#include <math.h>
#include "comm.h"
#include "screen.h"
#include "sound.h"

WAVheader readwavhdr(FILE *fp) {
	WAVheader myh;
	fread(&myh, sizeof(myh), 1, fp);
	return myh;
}

void displaywavhdr(WAVheader h) {
	printf("Chunk ID: ");
	for(int i = 0; i < 4; i++)
		printf("%c", h.chunkID[i]);
	printf("\nChunk size: %d\n", h.chunkSize);
	printf("Number of channels: %d\n", h.numChannels);
	printf("Sample rate: %d\n", h.sampleRate);
	printf("Block align: %d\n", h.blockAlign);
	printf("Bits per sample: %d\n", h.bitsPerSample);
}

void wavdata(WAVheader h, FILE *fp) {
	//in this function we will read sound samples from the opened file
	//the samples are calculated in to decibel values using Root Mean Square
	//(RMS) formula. We will display a 5-sec recorded sound into bar chart
	//our sound file uses sample rate of 16000, for 5 seconds, there are
	//5*16000 = 80000 samples, we want to display them into 160 bars
	short samples[500];
	int peaks = 0, flag = 0;
	double max = 0;

	for(int i = 0; i < 160; i++) {
		fread(samples, sizeof(samples), 1, fp);
		double sum = 0.0;
		for(int j = 0; j < 500; j++) {
			sum = sum + samples[j]*samples[j];
		}
		double result = sqrt(sum/500);
		result = 20*log10(result);
#ifdef SDEBUG
		printf("db[%d] = %f\n", i+1, result);
#else
		if(result > max) max = result;
		if(result > 60) {
			if(flag ==0) {
				flag = 1;
				peaks++;
			}
			setfgcolor(RED);
		}
		else {
			flag = 0;
		}
		drawbar(i+1, (int)result/3);
		resetcolor();
#endif
	}

	char sounddata[100];
	sprintf(sounddata, "peaks=%d&max=%f", peaks, max);
	senddata(sounddata, URL);

	gotoXY(1, 1);
	printf("Sample rate: %d\n", h.sampleRate);
	printf("The number of peak for this WAV file is: %d\n", peaks);
	printf("Duration: %f\n", (float)h.subchunk2Size/h.byteRate);
	printf("Maximum decibel value: %.2f decibels\n", max);
}
