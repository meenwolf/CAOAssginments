#include <stdio.h>

/*We use a array to iterate over the numbers and stuff*/
/*size is for the number of bit strings, so can be changed to a larger scope variable but it's not currently in this file so womp womp
int arr[] hopefully passes the memory address of our lovely array of bits :)
*/
int comparer(int arr[], int size){
for (int i = size-1; i >= 0; i--){
    for (int j = size-2; j >= 0; j--){
        int difference = arr[i] ^ arr[j];
        //call the calculator with this number
    }
}
}