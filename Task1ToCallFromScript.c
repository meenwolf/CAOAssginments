#include "hammingDistanceBitstring.h"

int main(int argc, char *argv[]) {
    if(argc !=4 ) {
        printf("missing arguments, Note that you have to run it from the terminal\n");
        printf("syntax: ./Task1ToCallFromScript nStrings stringLength seed\n");
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