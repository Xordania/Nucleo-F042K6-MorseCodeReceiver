#include <stdio.h>
#include <string.h>

// Remove the first removeAmount from the beginning of the array
int removeFromFront(char *array, int arrayLength, int removeAmount){
	if(arrayLength > removeAmount){
		memmove(array, array + removeAmount, arrayLength - removeAmount + 1);
		return 1;
	}else{
		return 0;
	}
}

int containsCharacter(char *array, int arrayLength, char c){
	for(int i = 0; i < arrayLength; i++){
		if(strcmp(array[i], c) == 0){
			return 1;
		}
	}

	return 0;
}

int findIndexChar(char c, char *arr, int length){
	int i;
	for(i = 0; i < length; i ++){
		if(arr[i] == c){
			return i;
		}
	}

	//Returns -1 if the specified character is not in the array
	return -1;
}
