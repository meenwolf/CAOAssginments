#include <stdio.h>

/*final version of first assignment, it works :) (gaslighting 101)
*/



//generator

//comparer function
int comparer(int arr[], int size){
    //get a size variable in our scope, we don't want to be changing the important one!
    int oursize = size;
//grab the last element in the array and take it with us
for (int i = oursize-1; i >= 0; i--){
//grab the second-to-last element and the third-to-last, etc. afterwards
    for (int j = oursize-2; j >= 0; j--){
//compare the last element to each element before it and call the calculator method
        int difference = arr[i] ^ arr[j];
        //call the calculator with this number
        return difference;
    }
    int oursize = oursize - 1; //remove the last element in the array
    return 0;
}
}

// this function will calculate the Hamming distance between 2 integers
int calcHam(int a, int b) {
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