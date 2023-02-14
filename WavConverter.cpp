#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "WavProcessing.h"

using namespace std;

//If any of these are defined as -1, the console will prompt for a value
int createRaw = -1;
int createText = -1;
int createWav = -1;

int targetChannels = -1;			//if -1, prompt user. otherwise should be 1 or 2
int targetBitsPerSample = -1;		//if -1, prompt user. otherwise should be 8/16/24

int appendAttr = 0;

int main(int argc, char* argv[])
{

	char filenameIn[256];
	char filenameOut[256];

	if (argc == 1) {
		cout << "Warning. No files passed as argument, so converting hardcoded filename\n" << endl;
	}

	int input;
	bool inputReset;

	if (createWav == -1) {
		input = -1;
		inputReset = true;

		while (input != 0 && input != 1) {

			if (!inputReset)
				cout << "Input Error" << endl;

			cout << "Do you wish to create wav?" << endl;
			cout << "1 - Yes" << endl;
			cout << "0 - No" << endl;
			cin >> input;
		}

		createWav = input;
	}
	else if (createWav != 0 && createWav != 1) {
		cout << "Predefined value not valid" << endl;
		system("PAUSE");
		return 1;
	}

	if (createRaw == -1) {
		input = -1;
		inputReset = true;

		while (input != 0 && input != 1) {

			if (!inputReset)
				cout << "Input Error" << endl;

			cout << "Do you wish to create raw?" << endl;
			cout << "1 - Yes" << endl;
			cout << "0 - No" << endl;
			cin >> input;
		}

		createRaw = input;
	}
	else if (createRaw != 0 && createRaw != 1) {
		cout << "Predefined value not valid" << endl;
		system("PAUSE");
		return 1;
	}

	if (createText == -1) {
		input = -1;
		inputReset = true;

		while (input != 0 && input != 1) {

			if (!inputReset)
				cout << "Input Error" << endl;

			cout << "Do you wish to create text?" << endl;
			cout << "1 - Yes" << endl;
			cout << "0 - No" << endl;
			cin >> input;
		}

		createText = input;
	}
	else if (createText != 0 && createText != 1) {
		cout << "Predefined value not valid" << endl;
		system("PAUSE");
		return 1;
	}


	input = -1;
	inputReset = true;

	while (input < 0 || input > 1) {

		if (!inputReset)
			cout << "Input Error" << endl;

		cout << "Do you wish to append attributes to filename?" << endl;
		cout << "1 - Yes" << endl;
		cout << "0 - No" << endl;

		cin >> input;
	}
	appendAttr = input;


	if (targetChannels == -1) {

		input = 0;
		inputReset = true;

		while (input != 1 && input != 2) {
			if (!inputReset)
				cout << "Input Error" << endl;
			cout << "How many channels do you require?" << endl;
			cout << "1 - Mono" << endl;
			cout << "2 - Stereo" << endl;

			cin >> input;
		}

		targetChannels = input;
	}
	else if (targetChannels != 1 && targetChannels != 2) {
		cout << "Predefined target channels not valid" << endl;
		system("PAUSE");
		return 1;
	}


	if (targetBitsPerSample == -1) {
		input = 0;
		inputReset = true;

		while (input != 8 && input != 16 && input != 24 && input != 32) {

			if (!inputReset)
				cout << "Input Error" << endl;

			cout << "What bit depth do you require" << endl;
			cout << "8 - 8 bit" << endl;
			cout << "16 - 16 bit" << endl;
			cout << "24 - 24 bit" << endl;
			//cout << "32 - 32 bit" << endl;		//to be implemented
			cin >> input;
		}

		targetBitsPerSample = input;
	}
	else if (targetBitsPerSample != 8 && targetBitsPerSample != 16 && targetBitsPerSample != 24) {
		cout << "Predefined bitdepth not valid" << endl;
		system("PAUSE");
		return 1;
	}


	int formatBits, commaSeparated, numberFormat, use0xPrefix;

	if (createText == 1) {

		cout << "\nText output format options" << endl;

		formatBits = 0;
		while (!(formatBits == 8 || formatBits == 16)) {
			cout << "Type 8 for 8-bit output, or 16 for 16-bit output\n";
			cin >> formatBits;
		}

		commaSeparated = -1;
		while (!(commaSeparated == 0 || commaSeparated == 1)) {
			cout << "Type 1  (true) or 0 (false) to use comma separated values \n";
			cin >> commaSeparated;
		}

		numberFormat = -1;
		while (!(numberFormat == 0 || numberFormat == 1)) {
			cout << "Type 0 for hex or 1 for decimal \n";
			cin >> numberFormat;
		}

		use0xPrefix = -1;
		if (numberFormat == 0) {
			while (!(use0xPrefix == 0 || use0xPrefix == 1)) {
				cout << "Type 1 (true) or 0 (false) to use 0x prefix \n";
				cin >> use0xPrefix;
			}
		}

	}


	for (int i = 1; i < argc; i++) {

		cout << "File " << i << " of " << argc-1 << endl;

		AUDIO_FILE audioFile;

		strcpy(filenameIn, argv[i]);
		strcpy(filenameOut, argv[i]);

		audioFile.OpenWavFile(filenameIn);

		int len = strlen(filenameOut);
		filenameOut[len - 3] = 'w';
		filenameOut[len - 2] = 'a';
		filenameOut[len - 1] = 'v';

		if (appendAttr == 1) {

			cout << "Appending attributes to filename: \"" << filenameOut << "\" ... \"";

			int len = strlen(filenameOut);

			char strToAppend[50];

			strToAppend[0] = ' ';
			strToAppend[1] = '_';

			if (targetChannels == 1) {
				strToAppend[2] = 'M';
			}
			else {
				strToAppend[2] = 'S';
			}

			strToAppend[3] = ' ';


			if (targetBitsPerSample == 16) {
				strToAppend[4] = '1';
				strToAppend[5] = '6';
				strToAppend[6] = 'b';
			}
			else if (targetBitsPerSample == 8) {
				strToAppend[4] = '0';
				strToAppend[5] = '8';
				strToAppend[6] = 'b';
			}
			else if (targetBitsPerSample == 24) {
				strToAppend[4] = '2';
				strToAppend[5] = '4';
				strToAppend[6] = 'b';
			}
			strToAppend[7] = '\0';

			filenameOut[len - 4] = '\0';
			strcat(filenameOut, strToAppend);

			strcat(filenameOut, "_");

			char strLength[10];
			_itoa(audioFile.length, strLength, 10);
			strcat(filenameOut, strLength);

			strcat(filenameOut, ".wav");

			cout << filenameOut << "\"" << endl;

		}

		if (targetChannels == 2) {
			if (audioFile.channels == 1) {
				audioFile.ConvertToStereo();
				cout << "Converting to stereo" << endl;
			}
		}
		else if (targetChannels == 1) {
			if (audioFile.channels == 2) {
				audioFile.ConvertToMono(MONO_MIX);
				cout << "Converting to mono" << endl;
			}
		}


		if (targetBitsPerSample != audioFile.bitsPerSample) {
			cout << "Updating bit depth" << endl;
			audioFile.UpdateDepth(targetBitsPerSample, targetChannels);
		}

		if (createText == 1) {

			int len = strlen(filenameOut);
			filenameOut[len - 3] = 't';
			filenameOut[len - 2] = 'x';
			filenameOut[len - 1] = 't';
			audioFile.SaveText(filenameOut, numberFormat, formatBits, use0xPrefix, commaSeparated);
		}

		if (createWav == 1) {

			int len = strlen(filenameOut);
			filenameOut[len - 3] = 'w';
			filenameOut[len - 2] = 'a';
			filenameOut[len - 1] = 'v';
			audioFile.SaveWav(filenameOut);
		}

		if (createRaw == 1){
			int len = strlen(filenameOut);
			filenameOut[len - 3] = 'r';
			filenameOut[len - 2] = 'a';
			filenameOut[len - 1] = 'w';
			audioFile.SaveRaw(filenameOut);
		}
	
		audioFile.Cleanup();
	}

	system("PAUSE");
	return 0;
}
