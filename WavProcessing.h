#pragma once

#include <stdint.h>
#include <fstream>
#include <iostream>
using namespace std;

#define	MONO_USE_L	0
#define MONO_USE_R	1
#define MONO_MIX	2

class AUDIO_FILE {

public:
	char filename[256];

	int sampleRate;
	int bitsPerSample;
	int channels;
	int length;
	int size;
	int audioFormat;

	int8_t* audioBuffer8 = NULL;
	int16_t* audioBuffer16 = NULL;
	int32_t* audioBuffer32 = NULL;
	float* audioBuffer32float = NULL;

	int ConvertToMono(int monoMode);
	int ConvertToStereo();
	int UpdateDepth(int targetBits, int channelsInUse);

	int OpenWavFile(char* filename) ;
	int SaveWav(char* filenameIn);
	int SaveRaw(char* filenameIn);
	int SaveText(char* filenameIn, int numberFormat, int formatBits, int use0xPrefix, int commaSeparated);
	
	void Cleanup();

};


