#include "stm32f0xx_hal.h"

/*
 * morseCode.h
 *
 *  Created on: 3 Jun 2023
 *      Author: Pillow sleeper
 */

#ifndef SRC_MORSECODE_H_
#define SRC_MORSECODE_H_

char* textToMorse(char* text);
int findIndexChar(char c, char *arr, int length);
int morseToSignal(char * morse, int length, GPIO_TypeDef* pinType, uint16_t pin);
void addTerminatingCharacter(char* morseCode);

#endif /* SRC_MORSECODE_H_ */
