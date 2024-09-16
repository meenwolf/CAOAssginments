// load useful libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// initiate functions
int getRandomDec();

int convertDecBin();
// Declare functions used in the main part of the code
int getRandomDec(int nmax) {
    srand(time(NULL));
    int range= pow(2,nmax);
    int r1 = rand()% range; //will be a random number from 0 to 1
    printf("r1 is now: %d", r1);
    return r1;

}

int convertDecBin(int decimal, int nBitsLim){
    int answer=0;
    while (nBitsLim >=0){
        int power2=pow(2, nBitsLim-1);
        int dec= decimal%power2;
        int power10= pow(10, nBitsLim-1);
        int addterm= dec*power10;
        answer= answer + addterm ;
        if (dec!=0){
            decimal=decimal-dec;
        }
        nBitsLim=nBitsLim-1;
    }
    return answer;
}

// Start the main part of the code
int main() {
    int nBits= 8;
    int decimalnum= getRandomDec(nBits);
    printf("We defined a function, lets test: %d", getRandomDec(nBits));
    printf("Made a converter, lets test it: %d", convertDecBin(decimalnum, nBits));
}

