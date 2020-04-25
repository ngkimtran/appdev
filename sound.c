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
	short samples[500];			//to read 500 samples from wav file
	int peaks = 0, flag = 0;	//1st value is to count, 2nd value to show that you're in a peak
	double max = 0;				//to find the maximum value

	for(int i = 0; i < 160; i++) {
		fread(samples, sizeof(samples), 1, fp);
		double sum = 0.0;		//accumulate the sum
		for(int j = 0; j < 500; j++) {
			sum = sum + samples[j]*samples[j];
		}
		double result = sqrt(sum/500);	//calculate the RMS value
		result = 20*log10(result);		//make sure the RMS value stays in the range of 20~90 dB
#ifdef SDEBUG
		printf("db[%d] = %f\n", i+1, result); //print the values in DEBUG mode
#else
		if(result > max) max = result;
		if(result > 60) {
			if(flag == 0) {
				flag = 1;			//if flag = 1 then we're already in a peak
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

	char sounddata[100];			//send data to the PHP program sound.php
	sprintf(sounddata, "peaks=%d&max=%f", peaks, max);
	senddata(sounddata, URL);

	gotoXY(1, 1);					//print out the result on top of the screen
	printf("Sample rate: %d\t", h.sampleRate);
	printf("Peaks: %d\t", peaks);
	printf("Duration: %f\t", (float)h.subchunk2Size/h.byteRate);
	printf("Maximum decibel value: %.2f decibels\n", max);
}
