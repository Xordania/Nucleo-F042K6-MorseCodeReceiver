#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "morseCode.h"
/*
 * morseCode.c
 *
 *  Created on: 3 Jun 2023
 *      Author: Pillow sleeper
 */


char* textToMorse(char* text){
	char *morseSignal = malloc(sizeof(char));
	//morseSignal[0] = 0;

	// 0 = Break of 1 beep long
	// 1 = Beep
	// 2 = Dash 3 beeps long
	// 3 = Break of 3 beeps long (Between letters)
	// 4 = Break of seven beeps long (Between word)

	// addTermiantingCharacter() adds a 5 to the end of the morseCode as a sign the signal is over for receiving transmissions

	char textUnits[37] = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
						'N',' O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0',
						'1', '2', '3', '4', '5', '6', '7', '8', '9'};

	// A 0 is placed between every two letters as there is a break of 1 beep between parts of the same letter
	const char *morseUnits[37] = {"4", "102", "2010101", "2010201", "20101", "1", "1010201", "20201", "1010101",
						   "101", "1020202", "20102", "1020101", "202", "201", "20202", "1020201", "2020102",
						   "10201", "10101", "2", "10102", "1010102", "10202", "2010102", "2010202", "2020101",
						   "102020202", "101020202", "101010202", "101010102", "101010101", "201010101", "202010101",
						   "202020101", "202020201", "202020202"};


	size_t textLength = strlen(text);
	/* Locates the currently iterated over char in the text variable, then uses its location within the text units array to
	 * find the corresponding Morse text.
	 * In Morse code there is a 3 beep gap after each word so this is also added in within the for-loop

	*/
	for(int i = 0; i < textLength; i++){
		printf("Current Morse Code: %s\n", morseSignal);

		// The index of the text unit and Morse units in their respective arrays
		int index = findIndexChar(toupper(text[i]), textUnits, strlen(textUnits));
		printf("Text: %c\n", text[i]);
		printf("Index: %d\n", index);

		size_t morseCodeSize = strlen(morseUnits[index]);
		//printf("Size of string: %d\n", morseCodeSize);

		/*
		 * When adding to a char array we need to allocate the additional memory for those additional characters.
		 * Another piece of memory is also created for the end of string character.
		*/

		size_t converterdLength = strlen(morseSignal);
		size_t newLength = converterdLength + morseCodeSize + 1;

		morseSignal = (char*)realloc(morseSignal, newLength);

		// Individually adds each character from the Morse Code unit to the end of the entire signal
		for(int j = 0; j < morseCodeSize; j ++){
			morseSignal[converterdLength + j] = morseUnits[index][j];
		}

		// Makes the final character the ending of the string
		morseSignal[converterdLength + morseCodeSize] = '\0';


		// Need to check if the next character is a blank space or not. If it is not then a 3 needs to be added to the code to show the gap between letters
		if(i < textLength - 1 && text[i + 1] != ' '){

				morseSignal = realloc(morseSignal, newLength + 1);
				morseSignal[newLength - 1] = '3';
				morseSignal[newLength] = '\0';

				printf("Final Array Length: %d\n", strlen(morseSignal));
		}

		printf("Morse End of Loop: %s\n", morseSignal);

	}


	return morseSignal;
}

// This is a fucntion that simply add one character to the end of a given char*
// In this case it specifically adds a five as that is the designated terminating character for the morse signals
void addTerminatingCharacter(char* morseCode){
    char terminatingCharacter = '5';
    strncat(morseCode, &terminatingCharacter, 1);
}

int morseToSignal(char * morse, int length, GPIO_TypeDef* pinType, uint16_t pin){
   /*
	* 0 = Break of 1 beep long
	* 1 = Beep
	* 2 = Dash 3 beeps long
	* 3 = Break of 3 beeps long (Between letters)
	* 4 = Break of seven beeps long (Between word)
	* 5 = End of Signal
	*/


	// A beep is 50 milliseconds
	int beepInMili = 50;
	int i = 0;

	while(i < length){
		char currentNumber = morse[i];
		// Sets and resets the pins in accordance to the list above
		switch (currentNumber){
			case '0':
				HAL_GPIO_WritePin(pinType, pin, GPIO_PIN_RESET);
				HAL_Delay(beepInMili);
				break;
			case '1':
				HAL_GPIO_WritePin(pinType, pin, GPIO_PIN_SET);
				HAL_Delay(beepInMili);
				break;
			case '2':
				HAL_GPIO_WritePin(pinType, pin, GPIO_PIN_SET);
				HAL_Delay(3 * beepInMili);
				break;
			case '3':
				HAL_GPIO_WritePin(pinType, pin, GPIO_PIN_RESET);
				HAL_Delay(3 * beepInMili);
				break;
			case '4':
				HAL_GPIO_WritePin(pinType, pin, GPIO_PIN_RESET);
				HAL_Delay(7 * beepInMili);
				break;
			case '5':
				HAL_GPIO_WritePin(pinType, pin, GPIO_PIN_SET);
				return 1;
			default: // If this is called something has gone wrong and the function return a 0 to show an error
				HAL_GPIO_WritePin(pinType, pin, GPIO_PIN_SET);
				return 0;
		}
		i++;
	}
	// It is assumed that by reaching this point the Morse Code has transmitted successfully
	return 1;
}

