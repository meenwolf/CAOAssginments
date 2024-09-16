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

#include <stdio.h>

// this function will calculate the hemming distance between 2 integers
int calcHem(int a, int b) {
    int x = a ^ b; 
    // now need to calculate the amount of 1's in the binary representation of x
    int d = 0;
    // the length of an int is 32 bits
    for (int i=0; i<32; i++) {
        d += 1 & x;
        x = x >> 1;
    }
    printf("hemming distance for %d and %d is %d.", a, b, d);
    // this function seems to work correctly!
}

// this function asks for the user's input
void askInput() {
    int nStrings, stringLength, seed;
    printf("How many strings should be generated?");
    scanf("%d", &nStrings);
    printf("How long should the strings be?");
    scanf("%d", &stringLength);
    printf("What seed should be used to generate the strings?");
    scanf("%d", &seed);
    printf("Input values were: number of strings = %d, of length = %d, with seed = %d.", nStrings, stringLength, seed);
}

int main() {
    // do main stuff
    calcHem(622, 827);
}