#include <stdio.h>

// Vitis stuff
// #include "platform.h"
// #include "xil_printf.h"

//
void shiftAndReplace(unsigned int fromPosition, unsigned int newValue);
void print_array(unsigned int *array, unsigned int length);
void sort(unsigned int *array, unsigned int length);

//
const int DATA_LENGTH = 8;
//

unsigned int data[] = {7, 4, 2, 12, 4, 6, 4, 100};
unsigned int sorted_data[DATA_LENGTH] = {};

int main() {
	// Vitis stuff
	//init_platform();

	// Sorts the array "data", that is in this case used as a ROM
	sort(data, DATA_LENGTH);

	// Prints out the sorted array
	print_array(sorted_data, DATA_LENGTH);

	// Vitis stuff
	//cleanup_platform();
	return 0;
}

void sort(unsigned int *array, unsigned int length) {
	for (int i = 0; i < length; i++){
		if((i == 0)){
			sorted_data[i] = array[i];
		} else {
			for(int j = 0; j < length; j++){
				// If true, then move every element in the array to the right
				if(sorted_data[j] > array[i]){
					// Logic for moving and replacing here
					shiftAndReplace(j, array[i]);
					break;
				} else if (sorted_data[j] == '\0' && sorted_data[j-1] != '\0') {
					// Else if the element is bigger, we place it in the empty spot
					sorted_data[j] = array[i];
					break;
				}
			}
		}
	}
}

void shiftAndReplace(unsigned int fromPosition, unsigned int newValue){
	for(int i = DATA_LENGTH; i > fromPosition; i--){
		sorted_data[i] = sorted_data[i-1];
	}
	sorted_data[fromPosition] = newValue;
}

void print_array(unsigned int *array, unsigned int length) {
	printf("Sorted Array: ");
	for (int i = 0; i < length; ++i) {
		char buffer[DATA_LENGTH];
		sprintf(buffer, "%2d%s", array[i], i + 1 == length ? "" : ", ");
		printf(buffer);
	}
	printf("\n");
}

