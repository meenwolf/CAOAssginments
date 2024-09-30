#include <stdio.h>

/*We use a array to iterate over the numbers and stuff*/
/*size is for the number of bit strings, so can be changed to a larger scope variable but it's not currently in this file so womp womp
int arr[] hopefully passes the memory address of our lovely array of bits :)
*/
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
int main(){

    int arr[5] = {1,3,4,2,5};

    printf("It's a beatiful: %d, world.",comparer(arr, 5));
}
