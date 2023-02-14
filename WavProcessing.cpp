#include "WavProcessing.h"

int AUDIO_FILE::ConvertToMono(int monoMode) {

	if (channels == 1)	return 0;		//error, already mono

	if (bitsPerSample == 8) {

		int8_t* audioBuffer8_temp;
		audioBuffer8_temp = new int8_t[length];

		switch (monoMode) {
		case MONO_USE_L: {

			for (int i = 0; i < length; i++) {
				audioBuffer8_temp[i] = audioBuffer8[i * 2 + 0];
			}

		}break;

		case MONO_USE_R: {

			for (int i = 0; i < length; i++) {
				audioBuffer8_temp[i] = audioBuffer8[i * 2 + 1];
			}

		}break;

		case MONO_MIX: {

			for (int i = 0; i < length; i++) {
				audioBuffer8_temp[i] = (audioBuffer8[i * 2 + 0] / 2);
				audioBuffer8_temp[i] += (audioBuffer8[i * 2 + 1] / 2);
			}

		}break;
		}	

		delete[] audioBuffer8;
		audioBuffer8 = audioBuffer8_temp;

		channels = 1;
		return 1;
	}

	else if (bitsPerSample == 16) {

		int16_t* audioBuffer16_temp;
		audioBuffer16_temp = new int16_t[length];

		switch (monoMode) {
		case MONO_USE_L: {

			for (int i = 0; i < length; i++) {
				audioBuffer16_temp[i] = audioBuffer16[i * 2 + 0];
			}

		}break;

		case MONO_USE_R: {

			for (int i = 0; i < length; i++) {
				audioBuffer16_temp[i] = audioBuffer16[i * 2 + 1];
			}

		}break;

		case MONO_MIX: {

			for (int i = 0; i < length; i++) {
				audioBuffer16_temp[i] = (audioBuffer16[i * 2 + 0] / 2);
				audioBuffer16_temp[i] += (audioBuffer16[i * 2 + 1] / 2);
			}

		}break;
		}	//switch monoMode

		delete[] audioBuffer16;
		audioBuffer16 = audioBuffer16_temp;

		channels = 1;
		return 1;

	}
	else if (bitsPerSample == 24) {

		int32_t* audioBuffer32_temp;
		audioBuffer32_temp = new int32_t[length * 2];

		switch (monoMode) {
		case MONO_USE_L: {

			for (int i = 0; i < length; i++) {
				audioBuffer32_temp[i] = audioBuffer32[i * 2 + 0];
			}

		}break;

		case MONO_USE_R: {

			for (int i = 0; i < length; i++) {
				audioBuffer32_temp[i] = audioBuffer32[i * 2 + 1];
			}

		}break;

		case MONO_MIX: {

			for (int i = 0; i < length; i++) {
				audioBuffer32_temp[i] = (audioBuffer32[i * 2 + 0] / 2);
				audioBuffer32_temp[i] += (audioBuffer32[i * 2 + 1] / 2);
			}

		}break;
		}	//switch monoMode


		delete[] audioBuffer32;
		audioBuffer32 = audioBuffer32_temp;

		channels = 1;
		return 1;
	}

	return 1;
}


int AUDIO_FILE::ConvertToStereo() {

	if (channels == 2) 
		return 0;

	switch(bitsPerSample){

		case 8:{
			int8_t* audioBuffer8_temp;
			audioBuffer8_temp = new int8_t[length * 2];

			for (int i = 0; i < length; i++) {
				audioBuffer8_temp[i * 2] = audioBuffer8[i];
				audioBuffer8_temp[i * 2 + 1] = audioBuffer8[i];
			}

			delete[] audioBuffer8;
			audioBuffer8 = audioBuffer8_temp;

			channels = 2;
			return 1;
		}break;
		
		case 16: {
			int16_t* audioBuffer16_temp;
			audioBuffer16_temp = new int16_t[length * 2];

			for (int i = 0; i < length; i++) {
				audioBuffer16_temp[i * 2] = audioBuffer16[i];
				audioBuffer16_temp[i * 2 + 1] = audioBuffer16[i];
			}

			delete[] audioBuffer16;
			audioBuffer16 = audioBuffer16_temp;

			channels = 2;
			return 1;

		} break;

		case 24: {
			int32_t* audioBuffer32_temp;
			audioBuffer32_temp = new int32_t[length * 2];

			for (int i = 0; i < length; i++) {
				audioBuffer32_temp[i * 2] = audioBuffer32[i];
				audioBuffer32_temp[i * 2 + 1] = audioBuffer32[i];
			}

			delete[] audioBuffer32;
			audioBuffer32 = audioBuffer32_temp;

			channels = 2;
			return 1;

		}break;

		case 32:{
			if (audioFormat == 0x0003) {			//FLOAT

				float* audioBuffer32float_temp;
				audioBuffer32float_temp = new float[length * 2];

				for (int i = 0; i < length; i++) {
					audioBuffer32float_temp[i * 2] = audioBuffer32float[i];
					audioBuffer32float_temp[i * 2 + 1] = audioBuffer32float[i];
				}

				delete[] audioBuffer32float;
				audioBuffer32float = audioBuffer32float_temp;

				channels = 2;
				return 1;

			}
			else if (audioFormat == 0x0001) {			

				int32_t* audioBuffer32_temp;
				audioBuffer32_temp = new int32_t[length * 2];

				for (int i = 0; i < length; i++) {
					audioBuffer32_temp[i * 2] = audioBuffer32[i];
					audioBuffer32_temp[i * 2 + 1] = audioBuffer32[i];
				}

				delete[] audioBuffer32;
				audioBuffer32 = audioBuffer32_temp;

				channels = 2;
				return 1;
			}

		} break;

	}

	return 0;

}

int AUDIO_FILE::UpdateDepth(int targetBits, int channelsInUse) {

	switch(targetBits){

		case 8: {			

			int8_t* audioBuffer8_temp;
			audioBuffer8_temp = new int8_t[length * channelsInUse];

			if (bitsPerSample == 16)
			{
				for (int i = 0; i < length * channelsInUse; i++)
				{
					audioBuffer8_temp[i] = (int8_t)(audioBuffer16[i] >> 8) + 128;
				}
				delete [] audioBuffer16;
				audioBuffer16 = NULL;

			}
			else if (bitsPerSample == 24)
			{
				for (int i = 0; i < length * channelsInUse; i++)
				{
					audioBuffer8_temp[i] = (int8_t)(audioBuffer16[i] >> 24);
				}
				delete [] audioBuffer32;
				audioBuffer32 = NULL;
			}
			audioBuffer8 = audioBuffer8_temp;
			bitsPerSample = targetBits;
		}break;

		case 16: {

			int16_t* audioBuffer16_temp;
			audioBuffer16_temp = new int16_t[length * channelsInUse];

			if (bitsPerSample == 8) {

				for (int i = 0; i < length * channelsInUse; i++) {
					audioBuffer16_temp[i] = (int16_t)((audioBuffer8[i] - 128) * 65536);
				}

				audioBuffer16 = audioBuffer16_temp;
				bitsPerSample = targetBits;
				delete [] audioBuffer8;
				audioBuffer8 = NULL;

				return 1;
			}
			else if (bitsPerSample == 24) {

				for (int i = 0; i < length * channelsInUse; i++) {
					audioBuffer16_temp[i] = (int16_t)(audioBuffer32[i] >> 8);
				}

				audioBuffer16 = audioBuffer16_temp;
				bitsPerSample = targetBits;
				delete [] audioBuffer32;
				audioBuffer32 = NULL;

				return 1;
			}

			else if (bitsPerSample == 32) {

				if (audioFormat == 0x0003) {			//FLOAT

					float min = 0.0f, max = 0.0f;
					for (int i = 0; i < length * channelsInUse; i++) {

						float x = audioBuffer32float[i];

						if (x > max) {
							max = x;
						}
						if (x < min) {
							min = x;
						}

						float floatValue = x * 32767.0f;
						audioBuffer16_temp[i] = (int16_t)floatValue;
					}

					float mm = min;
					delete [] audioBuffer32float;
					audioBuffer32float = NULL;
				}
				else if (audioFormat == 0x0001) {
					for (int i = 0; i < length * channelsInUse; i++) {
						audioBuffer16_temp[i] = (int16_t)(audioBuffer32[i] >> 16);
					}
					
					delete [] audioBuffer32;
					audioBuffer32 = NULL;
				}

				audioBuffer16 = audioBuffer16_temp;

				bitsPerSample = targetBits;

				return 1;
			}

		} break;

		case 24: {

			int32_t* audioBuffer32_temp;
			audioBuffer32_temp = new int32_t[length * channelsInUse];

			if (bitsPerSample == 8) {

				for (int i = 0; i < length * channelsInUse; i++) {
					audioBuffer32_temp[i] = (int32_t)((audioBuffer8[i] - 128) * 65536);
				}

				audioBuffer32 = audioBuffer32_temp;
				bitsPerSample = targetBits;
				delete [] audioBuffer8;
				audioBuffer8 = NULL;

				return 1;

			}
			else if (bitsPerSample == 16) {

				for (int i = 0; i < length * channelsInUse; i++) {
					audioBuffer32_temp[i] = (int32_t)(audioBuffer16[i] * 256);
				}

				audioBuffer32 = audioBuffer32_temp;
				bitsPerSample = targetBits;
				delete [] audioBuffer16;
				audioBuffer16 = NULL;

				return 1;
			}
		} break;

	}

	return 0;
}


void AUDIO_FILE::Cleanup() {

	if (audioBuffer8) {
		delete[] audioBuffer8;
		audioBuffer8 = NULL;
	}
	if (audioBuffer16) {
		delete[] audioBuffer16;
		audioBuffer16 = NULL;
	}
	if (audioBuffer32) {
		delete[] audioBuffer32;
		audioBuffer32 = NULL;
	}
	if (audioBuffer32float) {
		delete[] audioBuffer32float;
		audioBuffer32float = NULL;
	}

}

int AUDIO_FILE::OpenWavFile(char* filename) {

	ifstream audiofile;
	audiofile.open(filename, ios::in | ios::binary);

	audiofile.seekg(0, ios::end);
	int  sizeFile = audiofile.tellg();
	if (sizeFile == -1)
		return -1;
	audiofile.seekg(0, ios::beg);

	cout << "Opening Wav File: \"" << filename << "\"" << endl;

	cout << "\t";
	cout << "sizeFile: " << sizeFile << endl;

	char chunkId[4];
	audiofile.read(chunkId, 4);         //Contains the letters "RIFF" in ASCII form
										//(0x52494646 big-endian form).

	char chunkSize[4];
	audiofile.read(chunkSize, 4);         //This is the size of the rest of the chunk following this number. Little endian format


	int chunkSizeBytes = ((int)chunkSize[0] & 0xff) + (((int)chunkSize[1] & 0xff) << 8) + (((int)chunkSize[2] & 0xff) << 16) + (((int)chunkSize[3] & 0xff) << 24);

	cout << "\t";
	cout << "chunkSizeBytes: " << chunkSizeBytes << endl;

	char waveDef[4];
	audiofile.read(waveDef, 4);         //Contains the letters "WAVE"      

	/////////////////////////////////////////////////////////////////////
	//We now hav 2 subchunks: "fmt " and "data" 
	/////////////////////////////////////////////////////////////////////

	char subchunk1ID[4];
	audiofile.read(subchunk1ID, 4);         //Contains the letters "fmt " in ASCII form     

	char subchunk1SizeTemp[4];
	audiofile.read(subchunk1SizeTemp, 4);

	int subChunkSizeBytes = ((int)subchunk1SizeTemp[0] & 0xff) + (((int)subchunk1SizeTemp[1] & 0xff) << 8) + (((int)subchunk1SizeTemp[2] & 0xff) << 16) + (((int)subchunk1SizeTemp[3] & 0xff) << 24);
	//size is 16 which means PCM 
	cout << "\t";
	cout << "subChunkSizeBytes: " << subChunkSizeBytes << endl;

	char audioFormatTemp[2];
	audiofile.read(audioFormatTemp, 2);
	audioFormat = (int)audioFormatTemp[0] + ((int)audioFormatTemp[1] << 8);
	if (audioFormat == 0x0003) {
		cout << "WAVE_FORMAT_IEEE_FLOAT	IEEE float format" << endl;
	}

	cout << "\t";
	cout << "audioFormat: " << audioFormat << endl;

	char numChannelsTemp[2];
	audiofile.read(numChannelsTemp, 2);
	channels = (int)numChannelsTemp[0] + ((int)numChannelsTemp[1] << 8);

	char sampleRateTemp[4];
	audiofile.read(sampleRateTemp, 4);
	sampleRate = ((int)sampleRateTemp[0] & 0xff) + (((int)sampleRateTemp[1] & 0xff) << 8) + (((int)sampleRateTemp[2] & 0xff) << 16) + (((int)sampleRateTemp[3] & 0xff) << 24);

	char byteRateTemp[4];
	audiofile.read(byteRateTemp, 4);
	int byteRate = ((int)byteRateTemp[0] & 0xff) + (((int)byteRateTemp[1] & 0xff) << 8) + (((int)byteRateTemp[2] & 0xff) << 16) + (((int)byteRateTemp[3] & 0xff) << 24);

	char blockAlignTemp[2];
	audiofile.read(blockAlignTemp, 2);
	int blockAlign = ((int)blockAlignTemp[0] & 0xff) + (((int)blockAlignTemp[1] & 0xff) << 8);			//NumChannels * BitsPerSample/8
	cout << "\t" << "blockAlign: " << blockAlign << endl;

	char bitsPerSampleTemp[2];
	audiofile.read(bitsPerSampleTemp, 2);
	bitsPerSample = ((int)bitsPerSampleTemp[0] & 0xff) + (((int)bitsPerSampleTemp[1] & 0xff) << 8);		//eg 16 or 24

	cout << "\t" << "bitsPerSample: " << bitsPerSample << endl;
	//sometimes subChunkSizeBytes is 18 (or possibly something else?) - so read additional bytes; usually these can be ignored
	if (subChunkSizeBytes > 16) {
		char crap[256];
		audiofile.read(crap, subChunkSizeBytes - 16);
	}


	/////////////////////////////////////////////////////////////////////
	// Read second subchunk. Could be data, could be "acid", "pad ","smpl", etc
	///////////////////////////////////////////////////////////////////// 


	char subChunk2Id[4];
	audiofile.read(subChunk2Id, 4);

	char subChunk2SizeTemp[4];
	audiofile.read(subChunk2SizeTemp, 4);
	int subChunk2Size = ((int)subChunk2SizeTemp[0] & 0xff) + (((int)subChunk2SizeTemp[1] & 0xff) << 8) + (((int)subChunk2SizeTemp[2] & 0xff) << 16) + (((int)subChunk2SizeTemp[3] & 0xff) << 24);
	cout << "\t" << "subChunk2Size: " << subChunk2Size << endl;

	//If its data.... NumSamples * NumChannels * BitsPerSample/8
	//Raw file size : 26,456 bytes, which is this value!!!
	// other is 88,200

	while (!(subChunk2Id[0] == 'd' && subChunk2Id[1] == 'a' && subChunk2Id[2] == 't' && subChunk2Id[3] == 'a')) {
		//Keep searching until we find "data"; not bothered about other things

		for (int i = 0; i < subChunk2Size; i++) {

			char trash[1];
			audiofile.read(trash, 1);

		}


		audiofile.read(subChunk2Id, 4);         //Contains the letters "data" in ASCII form
												//cout << "\nsubChunk2Id: " << subChunk2Id;

		audiofile.read(subChunk2SizeTemp, 4);


		cout << "\t" << "subChunk2Id: " << subChunk2Id[0] << subChunk2Id[1] << subChunk2Id[2] << subChunk2Id[3] << endl;

		subChunk2Size = ((int)subChunk2SizeTemp[0] & 0xff) + (((int)subChunk2SizeTemp[1] & 0xff) << 8) + (((int)subChunk2SizeTemp[2] & 0xff) << 16) + (((int)subChunk2SizeTemp[3] & 0xff) << 24);
		//cout << "\nsubChunk2Size: " << subChunk2Size;         //NumSamples * NumChannels * BitsPerSample/8
		//Raw file size : 26,456 bytes, which is this value!!!
		// other is 88,200


	}


	sizeFile = subChunk2Size;
	cout << "\t" << "sizeFile: " << sizeFile << endl;

	//frames (regardless of channels)
	int frames = 0;

	if (bitsPerSample == 8) {
		frames = sizeFile;
	}
	else if (bitsPerSample == 16) {
		frames = sizeFile / 2;
	}
	else if (bitsPerSample == 24) {
		frames = sizeFile / 3;
	}
	else if (bitsPerSample == 32) {
		frames = sizeFile / 4;
	}

	if (channels == 2) {
		frames = frames / 2;
	}

	length = frames;

	cout << "\t" << "length: " << length << endl;

	if (bitsPerSample == 8) {

		audioBuffer8 = new int8_t[frames * channels];

		char c[1];
		for (int i = 0; i < sizeFile; i++) {

			audiofile.read(c, 1);
			audioBuffer8[i] = (c[0]);
		}

	}
	else if (bitsPerSample == 16) {

		if (audioBuffer16 != NULL) {
		}

		audioBuffer16 = new int16_t[frames * channels];

		char tempC[1];
		char c[1];
		for (int i = 0; i < sizeFile; i++) {

			audiofile.read(c, 1);
			//audiofileOut.write (c, 1);

			if (i % 2 == 1) {
				audioBuffer16[i / 2] = (int16_t)((c[0] << 8) | (tempC[0] & 0xff));
				//myfile2 <<  "\na: " << dec << a;
			}
			else {
				tempC[0] = c[0];
			}
		}

	}
	else if (bitsPerSample == 24) {

		if (audioBuffer32 != NULL) {
			//delete[] audioBuffer32;
			//audioBuffer32 = NULL;
		}
		audioBuffer32 = new int32_t[frames * channels];

		char tempC[2];
		char c[1];
		for (int i = 0; i < sizeFile; i++) {

			audiofile.read(c, 1);

			if (i % 3 == 2) {
				audioBuffer32[i / 3] = (int32_t)((c[0] << 16) | ((tempC[1] & 0xff) << 8) | (tempC[0] & 0xff));
			}
			else if (i % 3 == 1) {
				tempC[1] = c[0];
			}
			else {
				tempC[0] = c[0];
			}
		}

	}


	/*
	Look at your RIFF header. This will tell you the endianness of the Wav file.

	Use that endian-ness to read in your 32-bit floats correctly. For example: If your system is
	little endian (say, based on an x86 processor) and your wav file is big endian
	(say, created on an old PPC mac), you will need to do a 32-bit endian swap after
	you read in the data so that your float variable actually contains data that makes
	sense (this is usually a value between -1.0f and 1.0f )

	float f1 = 1.0e5;
	int   i1 = *reinterpret_cast<int*>( &f1 );
	// i1 = 1203982336, not 100000
	if you cannot avoid getting the wrong value, then to get the 'correct' value back, you need to reverse reinterpretation

	float f2 = *reinterpret_cast<float*>( &i1 );
	// f2 = 1.0e5
	*/


	else if (bitsPerSample == 32) {

		if (audioFormat == 0x0003) {			//FLOAT
			audioBuffer32float = new float[frames * channels];

			char tempC[3];
			char c[1];
			for (int i = 0; i < sizeFile; i++) {


				//Dulcimer... first 4 bytes = 00,00,b6,bb
				//correct order is bbb60000 = -0.00555419921875
				audiofile.read(c, 1);

				if (i < 20)		cout << "c: " << hex << (c[0] & 0xff) << endl;

				if (i % 4 == 3) {

					int32_t tempy = (int32_t)(((tempC[0] & 0xff) << 0) | ((tempC[1] & 0xff) << 8) | ((tempC[0] & 0xff) << 16) | ((c[0] & 0xff) << 24));

					float output;

					*((unsigned char*)(&output) + 0) = tempC[0];
					*((unsigned char*)(&output) + 1) = tempC[1];
					*((unsigned char*)(&output) + 2) = tempC[2];
					*((unsigned char*)(&output) + 3) = c[0];


					audioBuffer32float[i / 4] = output;

					if ((i / 4) < 50)	cout << "audioBuffer32float: " << audioBuffer32float[i / 4] << endl;

				}
				else if (i % 4 == 2) {
					tempC[2] = c[0];
				}
				else if (i % 4 == 1) {
					tempC[1] = c[0];
				}
				else {
					tempC[0] = c[0];
				}
			}

		}
		else if (audioFormat == 0x0001) {
			audioBuffer32 = new int32_t[frames * channels];

			char tempC[3];
			char c[1];
			for (int i = 0; i < sizeFile; i++) {

				audiofile.read(c, 1);

				if (i < 4)		cout << "c: " << hex << (c[0] & 0xff) << endl;

				if (i % 4 == 3) {
					audioBuffer32[i / 4] = (int32_t)((c[0] << 24) | ((tempC[2] & 0xff) << 16) | ((tempC[1] & 0xff) << 8) | (tempC[0] & 0xff));
				}
				else if (i % 4 == 2) {
					tempC[2] = c[0];
				}
				else if (i % 4 == 1) {
					tempC[1] = c[0];
				}
				else {
					tempC[0] = c[0];
				}
			}

		}

		cout << "sizeFile about to copy" << sizeFile << endl;

	}


	audiofile.close();

	return 0;

}

int AUDIO_FILE::SaveWav(char* filenameIn) {

	ofstream audiofileOut;
	ofstream audiofileOut16bit;

	audiofileOut.open(filenameIn, ios::out | ios::binary);

	char chunkId[] = "RIFF";
	audiofileOut.write(chunkId, 4);         //Contains the letters "RIFF" in ASCII form
											//(0x52494646 big-endian form).



											//This is the size of the rest of the chunk following 
											//this number.This is the size of the entire file 
											//in bytes minus 8 bytes for the two fields not included 
											//in this count: ChunkID and ChunkSize.

											//Little endian format
											//int chunkSizeBytes = ((int)chunkSize[0] & 0xff) + (((int)chunkSize[1] & 0xff) << 8) + (((int)chunkSize[2] & 0xff) << 16) + (((int)chunkSize[3] & 0xff) << 24);
	
	int chunkSizeBytes = 0;			//4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)

	chunkSizeBytes += 4;

	chunkSizeBytes += 8;
	chunkSizeBytes += 16;			//subchunk 1 size

	chunkSizeBytes += 8;
	chunkSizeBytes += length * channels * bitsPerSample / 8; // data (subchunk 2 size)

	char chunkSize[4];
	chunkSize[0] = (char)(chunkSizeBytes & 0xff);
	chunkSize[1] = (char)((chunkSizeBytes >> 8) & 0xff);
	chunkSize[2] = (char)((chunkSizeBytes >> 16) & 0xff);
	chunkSize[3] = (char)((chunkSizeBytes >> 24) & 0xff);
	audiofileOut.write(chunkSize, 4);

	char waveDef[] = "WAVE";
	audiofileOut.write(waveDef, 4);

	///////////////////////////////////////////////
	//We now hav 2 subchunks: "fmt " and "data" 

	char subchunk1ID[] = "fmt ";
	audiofileOut.write(subchunk1ID, 4);         //Contains the letters "fmt " in ASCII form     

	int subChunkSizeBytes = 16;					//Forcing 16=PCM (sometimes its 18 or other values)
	char subchunk1SizeTemp[4];
	subchunk1SizeTemp[0] = (char)(subChunkSizeBytes & 0xff);
	subchunk1SizeTemp[1] = (char)((subChunkSizeBytes >> 8) & 0xff);
	subchunk1SizeTemp[2] = (char)((subChunkSizeBytes >> 16) & 0xff);
	subchunk1SizeTemp[3] = (char)((subChunkSizeBytes >> 24) & 0xff);
	audiofileOut.write(subchunk1SizeTemp, 4);


	//int audioFormat = 1;		//PCM = 1. Other values indicate some form of compression.
	char audioFormatTemp[2];
	audioFormatTemp[0] = (audioFormat & 0xFF);
	audioFormatTemp[1] = ((audioFormat >> 8) & 0xFF);
	audiofileOut.write(audioFormatTemp, 2);

	char numChannelsTemp[2];
	numChannelsTemp[0] = (channels & 0xFF);
	numChannelsTemp[1] = ((channels >> 8) & 0xFF);
	audiofileOut.write(numChannelsTemp, 2);

	char sampleRateTemp[4];
	sampleRateTemp[0] = (char)(sampleRate & 0xff);
	sampleRateTemp[1] = (char)((sampleRate >> 8) & 0xff);
	sampleRateTemp[2] = (char)((sampleRate >> 16) & 0xff);
	sampleRateTemp[3] = (char)((sampleRate >> 24) & 0xff);
	audiofileOut.write(sampleRateTemp, 4);

	int byteRate = sampleRate * channels * bitsPerSample / 8;
	char byteRateTemp[4];
	byteRateTemp[0] = (char)(byteRate & 0xff);
	byteRateTemp[1] = (char)((byteRate >> 8) & 0xff);
	byteRateTemp[2] = (char)((byteRate >> 16) & 0xff);
	byteRateTemp[3] = (char)((byteRate >> 24) & 0xff);
	audiofileOut.write(byteRateTemp, 4);

	int blockAlign = channels * bitsPerSample / 8;
	char blockAlignTemp[2];
	blockAlignTemp[0] = (char)(blockAlign & 0xff);
	blockAlignTemp[1] = (char)((blockAlign >> 8) & 0xff);
	audiofileOut.write(blockAlignTemp, 2);

	char bitsPerSampleTemp[2];
	bitsPerSampleTemp[0] = (char)(bitsPerSample & 0xff);
	bitsPerSampleTemp[1] = (char)((bitsPerSample >> 8) & 0xff);
	audiofileOut.write(bitsPerSampleTemp, 2);

	//second subchunk (can be data, or other)
	char subChunk2Id[] = "data";
	audiofileOut.write(subChunk2Id, 4);


	int subChunk2Size = length * channels * bitsPerSample / 8;			//fix
	char subChunk2SizeTemp[4];

	subChunk2SizeTemp[0] = (char)(subChunk2Size & 0xff);
	subChunk2SizeTemp[1] = (char)((subChunk2Size >> 8) & 0xff);
	subChunk2SizeTemp[2] = (char)((subChunk2Size >> 16) & 0xff);
	subChunk2SizeTemp[3] = (char)((subChunk2Size >> 24) & 0xff);
	audiofileOut.write(subChunk2SizeTemp, 4);

	if (bitsPerSample == 8) {

		for (int i = 0; i < length; i++) {

			int iI = i * channels;

			char buffer[2];
			buffer[0] = (char)(audioBuffer8[iI] & 0xff);


			if (channels == 2) {
				buffer[1] = (char)(audioBuffer8[iI + 1] & 0xff);
			}
			audiofileOut.write(buffer, 1 * channels);
		}
	}

	else if (bitsPerSample == 16) {

		for (int i = 0; i < length; i++) {

			int iI = i * channels;

			char buffer[4];
			buffer[0] = (char)(audioBuffer16[iI] & 0xff);
			buffer[1] = (char)((audioBuffer16[iI] >> 8) & 0xff);

			if (channels == 2) {
				buffer[2] = (char)(audioBuffer16[iI + 1] & 0xff);
				buffer[3] = (char)((audioBuffer16[iI + 1] >> 8) & 0xff);
			}
			audiofileOut.write(buffer, 2 * channels);
		}
	}

	else if (bitsPerSample == 24) {

		for (int i = 0; i < length; i++) {

			int iI = i * channels;

			char buffer[6];
			buffer[0] = (char)(audioBuffer32[iI] & 0xff);
			buffer[1] = (char)((audioBuffer32[iI] >> 8) & 0xff);
			buffer[2] = (char)((audioBuffer32[iI] >> 16) & 0xff);

			if (channels == 2) {
				buffer[3] = (char)(audioBuffer32[iI + 1] & 0xff);
				buffer[4] = (char)((audioBuffer32[iI + 1] >> 8) & 0xff);
				buffer[5] = (char)((audioBuffer32[iI + 1] >> 16) & 0xff);
			}
			audiofileOut.write(buffer, 3 * channels);
		}
	}


	else if (bitsPerSample == 32) {

		if (audioFormat == 0x01) {			//PCM

			for (int i = 0; i < length; i++) {

				int iI = i * channels;

				char buffer[8];
				buffer[0] = (char)(audioBuffer32[iI] & 0xff);
				buffer[1] = (char)((audioBuffer32[iI] >> 8) & 0xff);
				buffer[2] = (char)((audioBuffer32[iI] >> 16) & 0xff);
				buffer[3] = (char)((audioBuffer32[iI] >> 24) & 0xff);

				if (channels == 2) {
					buffer[4] = (char)(audioBuffer32[iI + 1] & 0xff);
					buffer[5] = (char)((audioBuffer32[iI + 1] >> 8) & 0xff);
					buffer[6] = (char)((audioBuffer32[iI + 1] >> 16) & 0xff);
					buffer[7] = (char)((audioBuffer32[iI + 1] >> 24) & 0xff);
				}
				audiofileOut.write(buffer, 4 * channels);
			}

		}

		else if (audioFormat == 0x03) {		//float

			for (int i = 0; i < length; i++) {

				int iI = i * channels;

				float f1 = audioBuffer32float[iI];
				audiofileOut.write((char*)&f1, 4);		//out.write((char *)&f1,sizeof(float));	
														//fl.write(reinterpret_cast<char*>(&f),sizeof(float));

				if (channels == 2) {
					f1 = audioBuffer32float[iI + 1];
					audiofileOut.write((char*)&f1, 4);
				}
			}

		}

	}

	audiofileOut.close();

	return 1;

}


int AUDIO_FILE::SaveRaw(char* filenameIn) {

	ofstream audiofileOut;

	audiofileOut.open(filenameIn, ios::out | ios::binary);

	switch(bitsPerSample){

		case 8:{

			for (int i = 0; i < length; i++) {

				int iI = i * channels;

				char buffer[2];
				buffer[0] = (char)(audioBuffer8[iI] & 0xff);

				if (channels == 2) {
					buffer[1] = (char)(audioBuffer8[iI + 1] & 0xff);
				}
				audiofileOut.write(buffer, 1 * channels);
			}

		}break;

		case 16: {

			for (int i = 0; i < length; i++) {

				int iI = i * channels;

				char buffer[4];
				buffer[0] = (char)(audioBuffer16[iI] & 0xff);
				buffer[1] = (char)((audioBuffer16[iI] >> 8) & 0xff);

				if (channels == 2) {
					buffer[2] = (char)(audioBuffer16[iI + 1] & 0xff);
					buffer[3] = (char)((audioBuffer16[iI + 1] >> 8) & 0xff);
				}
				audiofileOut.write(buffer, 2 * channels);
			}

		}break;

		case 24: {

			for (int i = 0; i < length; i++) {

				int iI = i * channels;

				char buffer[6];
				buffer[0] = (char)(audioBuffer32[iI] & 0xff);
				buffer[1] = (char)((audioBuffer32[iI] >> 8) & 0xff);
				buffer[2] = (char)((audioBuffer32[iI] >> 16) & 0xff);

				if (channels == 2) {
					buffer[3] = (char)(audioBuffer32[iI + 1] & 0xff);
					buffer[4] = (char)((audioBuffer32[iI + 1] >> 8) & 0xff);
					buffer[5] = (char)((audioBuffer32[iI + 1] >> 16) & 0xff);
				}
				audiofileOut.write(buffer, 3 * channels);
			}
		} break;


		case 32:{

			if (audioFormat == 0x01) {			//PCM

				for (int i = 0; i < length; i++) {

					int iI = i * channels;

					char buffer[8];
					buffer[0] = (char)(audioBuffer32[iI] & 0xff);
					buffer[1] = (char)((audioBuffer32[iI] >> 8) & 0xff);
					buffer[2] = (char)((audioBuffer32[iI] >> 16) & 0xff);
					buffer[3] = (char)((audioBuffer32[iI] >> 24) & 0xff);

					if (channels == 2) {
						buffer[4] = (char)(audioBuffer32[iI + 1] & 0xff);
						buffer[5] = (char)((audioBuffer32[iI + 1] >> 8) & 0xff);
						buffer[6] = (char)((audioBuffer32[iI + 1] >> 16) & 0xff);
						buffer[7] = (char)((audioBuffer32[iI + 1] >> 24) & 0xff);
					}
					audiofileOut.write(buffer, 4 * channels);
				}

			}

			else if (audioFormat == 0x03) {		//float

				for (int i = 0; i < length; i++) {

					int iI = i * channels;

					float f1 = audioBuffer32float[iI];
					audiofileOut.write((char*)&f1, 4);		//out.write((char *)&f1,sizeof(float));	
															//fl.write(reinterpret_cast<char*>(&f),sizeof(float));

					if (channels == 2) {
						f1 = audioBuffer32float[iI + 1];
						audiofileOut.write((char*)&f1, 4);
					}
				}

			}

		} break;

	}

	audiofileOut.close();
	return 1;

}


int AUDIO_FILE::SaveText(char* filenameIn, int numberFormat, int formatBits, int use0xPrefix, int commaSeparated) {

	ofstream audiofileOut;
	audiofileOut.open(filenameIn, ios::out | ios::binary);

	ofstream myfile;
	myfile.open(filenameIn);

	int counter = 0;

	switch(bitsPerSample){

		case 8:{

		for (int i = 0; i < length * channels; i++) {

			unsigned int ba = audioBuffer8[i];
		

			if (counter != 0)
				myfile << " ";

			if (numberFormat == 0) {

				if (use0xPrefix)
					myfile << "0x";

				unsigned int c;

				c = (0xff & ba);
				if (c < 16)
					myfile << "0";

				myfile << hex << c;

			}
			else {
				myfile << (0xff & ba);
			}

			if (commaSeparated == 1)
				myfile << ",";

			counter++;
			if (counter == 16) {
				counter = 0;
				myfile << "\n";
			}

		}
		
	} break;

	case 16:{ 

		if (formatBits == 8) {

			bool groupThe2Bytes = true;

			for (int i = 0; i < length * channels; i++) {

				unsigned int ba = audioBuffer16[i];
				signed int baSigned = ba;


				if (counter != 0)
					myfile << " ";

				if (numberFormat == 0) {

					if (use0xPrefix)
						myfile << "0x";

					unsigned int c;

					c = (0x00ff & ba);
					if (c < 16)
						myfile << "0";

					myfile << hex << c;

					if (commaSeparated == 1)
						myfile << ",";
					if (!groupThe2Bytes)
						myfile << " ";

					if (use0xPrefix)
						myfile << "0x";

					c = ((0xff00 & ba) >> 8);
					if (c < 16)
						myfile << "0";
					myfile << hex << ((0xff00 & ba) >> 8);
				}
				else {
					myfile << (0x00ff & baSigned);
					if (commaSeparated == 1)
						myfile << ",";
					myfile << ((0xff00 & baSigned) >> 8);
				}

				if (commaSeparated == 1)
					myfile << ",";

				counter++;
				if (counter == 16) {
					counter = 0;
					myfile << "\n";
				}

			}
		}

		if (formatBits == 16) {

			for (int i = 0; i < length * channels; i++) {

				unsigned int ba = audioBuffer16[i];
				signed int baSigned = ba;


				if (counter != 0)
					myfile << " ";

				if (numberFormat == 0) {
					myfile << hex << (0xffff & ba);
				}
				else {
					myfile << (baSigned);
				}

				if (commaSeparated == 1)
					myfile << ",";

				counter++;
				if (counter == 16) {
					counter = 0;
					myfile << "\n";
				}

			}
		}

	} break;



	case 24: {

		for (int i = 0; i < length; i++) {

			int iI = i * channels;

			char buffer[6];
			buffer[0] = (char)(audioBuffer32[iI] & 0xff);
			buffer[1] = (char)((audioBuffer32[iI] >> 8) & 0xff);
			buffer[2] = (char)((audioBuffer32[iI] >> 16) & 0xff);

			if (channels == 2) {
				buffer[3] = (char)(audioBuffer32[iI + 1] & 0xff);
				buffer[4] = (char)((audioBuffer32[iI + 1] >> 8) & 0xff);
				buffer[5] = (char)((audioBuffer32[iI + 1] >> 16) & 0xff);
			}
			audiofileOut.write(buffer, 3 * channels);
		}
	} break;


	case 32: {

		if (audioFormat == 0x01) {			//PCM

			for (int i = 0; i < length; i++) {

				int iI = i * channels;

				char buffer[8];
				buffer[0] = (char)(audioBuffer32[iI] & 0xff);
				buffer[1] = (char)((audioBuffer32[iI] >> 8) & 0xff);
				buffer[2] = (char)((audioBuffer32[iI] >> 16) & 0xff);
				buffer[3] = (char)((audioBuffer32[iI] >> 24) & 0xff);

				if (channels == 2) {
					buffer[4] = (char)(audioBuffer32[iI + 1] & 0xff);
					buffer[5] = (char)((audioBuffer32[iI + 1] >> 8) & 0xff);
					buffer[6] = (char)((audioBuffer32[iI + 1] >> 16) & 0xff);
					buffer[7] = (char)((audioBuffer32[iI + 1] >> 24) & 0xff);
				}
				audiofileOut.write(buffer, 4 * channels);
			}

		}

		else if (audioFormat == 0x03) {		//float

			for (int i = 0; i < length; i++) {

				int iI = i * channels;

				float f1 = audioBuffer32float[iI];
				audiofileOut.write((char*)&f1, 4);		//out.write((char *)&f1,sizeof(float));	
														//fl.write(reinterpret_cast<char*>(&f),sizeof(float));

				if (channels == 2) {
					f1 = audioBuffer32float[iI + 1];
					audiofileOut.write((char*)&f1, 4);
				}
			}

		}


	} break;

	}

	audiofileOut.close();

	return 1;

}