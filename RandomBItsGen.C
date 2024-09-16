#include <stdio.h>
#include <stdlib.h>
int main() {
    double r1= rand(); //will be a random number from 0 to 1
    printf("our random: %lf", r1);
    printf("we have r1 divided by randmax: %lf", r1/RAND_MAX);
    if (r1/RAND_MAX > 0.5) {
        printf("We should return 1");
        }
    else {
       printf("we should return 0");
    }
    // printf("test rand %lf", r1/RAND_MAX);
}