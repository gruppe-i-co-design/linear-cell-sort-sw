#include <stdio.h>
// #include "platform.h"
// #include "xil_printf.h"

typedef unsigned int uint;

void shift_and_replace(uint *data, uint length, uint from_position,
                       uint new_value);
void print_array(uint *array, uint length);
void sort(uint *to, const uint *from, uint length);

#define DATA_LEN 8
uint data[DATA_LEN] = {7, 4, 2, 12, 4, 6, 4, 100};

int main() {
  // Vitis stuff
  // init_platform();

  fputs("\n\rbefore: ", stdout);
  print_array(data, DATA_LEN);

  uint sorted_data[DATA_LEN] = {};
  sort(sorted_data, data, DATA_LEN);

  fputs("\n\rafter: ", stdout);
  print_array(sorted_data, DATA_LEN);

  // Vitis stuff
  // cleanup_platform();
  return 0;
}

// Sorts data in from into to so that to is sorted.
//
// NB! to has to be zero-initialized.
void sort(uint *to, const uint *from, uint length) {
  // First value always goes into first cell
  to[0] = from[0];

  // Loop through each input value in from and process it through the "cells"
  for (int i = 1; i < length; i++) {

    // The following loop is done in parallel in hardware, however in software
    // we have implemented it sequentially because the syncronization needed for
    // doing this in parallel is quite tricky.
    for (int j = 0; j < length; j++) {

      // The rules for a cell encoded into C code. It is only if we make an
      // action that we move on to the next "cell" using break.
      if (to[j] > from[i]) {
        // New element is smaller so move every element in the array to the
        // right and insert as new value in front.
        shift_and_replace(to, DATA_LEN, j, from[i]);
        break;
      } else if (to[j] == 0 && (j == 0 || to[j - 1] != 0)) {
        // New element is bigger or equal, current "cell" is empty and previous
        // cell is full, so we place it in the empty "cell".
        to[j] = from[i];
        break;
      }
    }
  }
}

void shift_and_replace(uint *data, uint length, uint from_position,
                       uint new_value) {
  for (int i = DATA_LEN - 1; i > from_position; i--) {
    data[i] = data[i - 1];
  }
  data[from_position] = new_value;
}

void print_array(uint *array, uint length) {
  for (int i = 0; i < length; ++i) {
    char buffer[10];
    sprintf(buffer, "%2d%s", array[i], i + 1 == length ? "" : ", ");
    fputs(buffer, stdout);
  }
}
