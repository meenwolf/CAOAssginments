#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
// We use *, a pointer to indicate where 0 or more bools are stored. If we were to work with a fixed lenght, we could use an
// array, but due to varying lenghts of bitstrings, we need the pointer.
//Define a custom type to store the bitstring and its length
struct BitString {
    int length; // declare an attribute called length, to store the number of bits in data
    bool *data; // Declare an attribute called data to store the Pointer to the bitstring(our data)
};

BitString alloc_bit_string(int L) {
    // Allocate memory for the bitstring
    bool *data = (bool *)malloc(L * sizeof(bool));

    for(int i = 0 ; i < L; ++i) {
        data[i] = rand() & 1; // rand() generates a random number, already represented as bits, so use &
        // To only save 1 bit (the least signigicant)
    }

    BitString result;// initiate a result variable
    result.data = data; // store the data in the data attribute of result
    result.length = L; // store the number of bits data consists of, in the length attribute of result
    return result;
}

void print_bitstring(BitString b) {
    for(int i = 0; i < b.length; ++i) {
        printf("%d", b.data[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    int L = 123;
    BitString b = alloc_bit_string(L);
    print_bitstring(b);
}