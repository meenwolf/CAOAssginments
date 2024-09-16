#include "RandomBitsGenFast.h" //We can not include a C file, but we can include so called header files, which
// can be seen a C programm without a main, so just function declarations.
// I don't have to include libraries that I included in the RandomBitsGenFast.h file.

/* Write a C/C++ program that calculates the hamming distance between pairs of N binary
strings of length L. For simplicity, you should generate the strings randomly.
Your program should read three integer numbers from the command line: the number of
strings (N), the string length (L), and a seed for the random number generator (s). Your
program should first dynamically allocate memory, and randomly generate N strings.
Thereafter, the hamming distance for all possible pairs of the N strings should be calculated.
Your program should print the checksum (accumulation of all hamming distances) and the
average of all hamming distances and exit. Write a script that compiles your program and
calls it for L = 64, 89, and 256, and N = 100 and 1000.
The aim of this task is to understand the underlying computations.
Important:
- A “binary string” refers to the concept of an array of bits; it does not necessarily imply
that one should use actual strings to represent the data.
- Consider an efficient way to generate strings, keeping in mind that all data in a system
is represented as arrays of bits.
- Consider an efficient way to calculate and count the differences between the binary
strings. */


// this function will calculate the hemming distance between 2 integers
int HamDist2Strings(struct BitString a, struct BitString b) {
    int i=0;
    int result=0;
    while (i<a.length){
        for(int j = 7; j >= 0; --j) {
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
    float result=  totalHamDist/(float)(nBitstring*(nBitstring+1));
    printf("The average hamming distance is: %f \n",  result);

    return result;
}


// this function asks for the user's input. To do so, we need to make a structure to store the user input in
struct UserInput{
    int nStrings, stringLength, seed;
};

struct UserInput askInput() {
    struct UserInput resultingSettings;
    printf("How many strings should be generated?");
    scanf("%d", &resultingSettings.nStrings);
    printf("How long should the strings be?");
    scanf("%d", &resultingSettings.stringLength);
    printf("What seed should be used to generate the strings?");
    scanf("%d", &resultingSettings.seed);
    printf("Input values were: number of strings = %d, of length = %d, with seed = %d.",resultingSettings.nStrings,resultingSettings.stringLength, resultingSettings.seed);
    return resultingSettings;
}