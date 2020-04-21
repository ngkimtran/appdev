//in this  file we define related constants and declare functions
//for handling sound.

//#define SDEBUG

//define sound structure (deal with .wav files)

typedef struct {
	char chunkID[4];	//should always be "RIFF"
	int chunkSize;
	char format[4];		//should always be "WAVE"
	char subchunkID[4];	//should always be "fmt "
	int subchunk1Size;	//should be 16 for PCM
	short audioFormat;	//should be 1 for PCM
	short numChannels;	//should be 1 for mono, 2 for stereo
	int sampleRate;		//usually it's 44100 or 16000
	int byteRate;		//can be calculated
	short blockAlign;	//how many bytes in 1 block
	short bitsPerSample; //could be 8 or 16
	char subchunk2ID[4]; //should always be "data"
	int subchunk2Size;	//can be calculated
}WAVheader;



//function declaration
WAVheader readwavhdr(FILE *fp);
void displaywavhdr(WAVheader h);
void wavdata(WAVheader h, FILE *fp);
