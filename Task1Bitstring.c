#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
// We use *, a pointer to indicate where 0 or more bools are stored. If we were to work with a fixed lenght, we could use an
// array, but due to varying lenghts of bitstrings, we need the pointer.
//Define a custom type to store the bitstring and its length
struct BitString {
    int length; // declare an attribute called length, to store the number of bytes in data, assuming the lenght of the 
    // bitstring is always a multiple of 8, if not, we zeropad until it is.
    uint8_t *data; // Declare an attribute called data to store the Pointer to the bitstring(our data)
};

struct BitString alloc_bit_string(int L) {
    // Allocate memory for the bitstring
    int nbytes= (L+7)/8; //  normal division rounds down, we want up, hence the +7
    int restbits = nbytes*8 - L;
    uint8_t *data = (uint8_t *)malloc(nbytes);

    for(int i = 0 ; i < nbytes; ++i) {
        data[i] = rand() & 0xFF; // rand() generates a random number, already represented as bits, so use &
        // To only save the last 8 bits (the least signigicant)
    }

    if (restbits){
        data[nbytes-1] >>= restbits; // we zeropad on the left side, by shifting to the right since bits are random and not yet used
    }

    struct BitString result;// initiate a result variable
    result.data = data; // store the data in the data attribute of result
    result.length = nbytes; // store the number of bytes data consists of, in the length attribute of result
    return result;
}

void print_bitstring(struct BitString b) {
    for(int i = b.length-1; i >=0; --i) {
        for(int j = 7; j >= 0; --j) {
            printf("%d", (b.data[i] >> j) & 1); //first print the most significant bit, by shifting 7 to the right, then
            // second significant bit by shifting 6 to the right etc, those shifts are temporary, does not work inplace :)
        }
    }
    printf("\n");
}

// this function will calculate the hemming distance between 2 integers
int HamDist2Strings(struct BitString a, struct BitString b) {
    int i=0;
    int result=0;
    while (i<a.length){
        for(int j = 7; j >= 0; j--) {
            result=result + ((( a.data[i] ^ b.data[i])>>j)&1);
        }
        i=i+1;
    };
    // print_bitstring(a);
    // print_bitstring(b);
    // printf("and the hamming distance between those two bitstrings is: %d\n", result);
    return result;  

}

int TotalHamDistNLbitstrings(int nBitstrings, int lenghtBitstring){
    int totalHamDist=0;
    // BitString *arrbitstring = (BitString *)malloc(nStrings);

    struct BitString arrbitstrings[nBitstrings];
    int i=0;
    while (i<nBitstrings){
        arrbitstrings[i]= alloc_bit_string(lenghtBitstring);
        i=i+1;
    }
    //grab the first bitstring in the array and take it with us
    for (i=0; i< nBitstrings ; i++){
    //grab the second bitstring and the third etc. afterwards
        for (int j = i+1; j < nBitstrings; j++){
    //Calculate the hamming distance between the bitstrings
            int difference = HamDist2Strings(arrbitstrings[i], arrbitstrings[j]);
            totalHamDist=totalHamDist+difference;
    }
    }
    printf("The total hamming distance is: %d \n", totalHamDist);
    return totalHamDist;
}

float AverageHamDist(int totalHamDist, int nBitstring){
    float result=  totalHamDist/(float)(nBitstring*(nBitstring-1));
    printf("The average hamming distance is: %f \n",  result);

    return result;
}


int main(int argc, char *argv[]) {
    if(argc !=4 ) {
        printf("missing arguments, Note that you have to run it from the terminal\n");
        printf("syntax: First run cc -o Task1FromScript Task1Bitstring.c Then run: ./Task1FromScript nStrings stringLength seed\n");
        return 1;
    }

    printf("arguments %s %s %s %s\n", argv[0], argv[1], argv[2], argv[3]);
    int nStrings = atoi(argv[1]);
    int stringLength= atoi(argv[2]);
    int seed = atoi(argv[3]);

    srand(seed);
    printf("Test the Total hamming distance calculation of %d bitstrings, each of lenght %d, with seed %d \n",nStrings, stringLength, seed);
    int testTotalHam= TotalHamDistNLbitstrings(nStrings, stringLength);
    AverageHamDist(testTotalHam, nStrings);

}