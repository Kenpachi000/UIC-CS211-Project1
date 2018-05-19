#include <stdio.h>
#include <stdlib.h> 


/*
Gavin Wu
netID gwu23@uic.edu
CS 211 spring 2018
proj 1 */


//-----------------------------------------------------------------------------------------------------------------------------
void arrayCopy (int fromArray[], int toArray[], int size) {
    
    int i;
    
    // loop through entire array to do the copy
    for (i=0; i < size; i++) {
        
        toArray[i] = fromArray[i];
        
    }
}

//---------------------------------------------------------------------------------------------------------------------------
// this function is pretty much bubble sort
void sortArray (int arrayToSort[], int size) {
    
    int temp;              // use a temp variable to store a number to swap numbers around
    int i;              // use for loop
    int isDoneSwapping; // will be used as a counter to see if all numbers are in proper order
    
    while (1) {
        
        isDoneSwapping = 1;                              // used to know if there was a swap. if there was then it turns to 0
        
        for (i=0; i < size-1; i++) {
            
            if (arrayToSort[i] > arrayToSort[i+1]) {
                
                // if the left number is bigger than the right number, we do a swap
                temp = arrayToSort[i];
                arrayToSort[i] = arrayToSort[i+1];
                arrayToSort[i+1] = temp;
                isDoneSwapping = 0;                      // there was a swap so it is not in order
                
            }
            
        }
        
        // if the value of swapping doesnt change then the array is in order
        if (isDoneSwapping == 1) {
            break;
        }
        
    }
    
}
//--------------------------------------------------------------------------------------------------------------------------
int linearSearch (int arrayToSearch[], int size, int target, int *numComparisons) {
    
    int i;
    
    // loop through entire array one by one to see if there the number can be found
    for (i=0; i<size; i++) {
        
        //comparisons
        *numComparisons = *numComparisons + 1;
        
        if (arrayToSearch[i] == target) {
            return i;
        }
    }
    
    // not found
    return -1;
    
}
//----------------------------------------------------------------------------------------------------------------------------
int binarySearch (int arrayToSearch[], int size, int target, int *numComparisons) {
    
    int start = 0;
    int end = size-1; // arrays are from 0 to n-1
    int mid;
    
    while (start <= end) {
        
        mid = (start + end) / 2;
        
        //check how many times it searched
        *numComparisons = *numComparisons + 1;
        
        // found the number
        if (arrayToSearch[mid] == target) {
            return mid;
        }
        
        // the number we look for has to be on the left hand size so we adjust the end point to search left side only
        if (arrayToSearch[mid] > target) {
            end = mid-1;
        }
        
        // we know that the number will be on the right side so we adjust start value
        else {
            start = mid + 1;
            
        }
    }
    
    return -1;
    
}

//--------------------------------------------------------------------------------------------------------------------------
int main() {
    
    int userInput;
    int *userInputList; // will be used as dynamic array to store all the user inputs
    int *duplicatedList;
    int size = 10; // inital size of array will be 10
    int *tempArray; // used to help dynammically allocate memory
    int *tempArrayTwo;
    int counter = 0;
    int i;
    int linearSearchPosition = 0;
    int binarySearchPosition = 0;
    int numComparisonsForLinear;
    int numComparisonsForBinary;
    
    // creating the dynamic array (Took ideas from Professor Troy page)
    
    userInputList = (int *) malloc (size * sizeof(int) );
    
    duplicatedList = (int *) malloc (size * sizeof(int) );        // create the 2nd array
    

    printf ("Enter a list of numbers followed by -999 to stop\n");
    
    // prompt user to enter numbers until they hit -999
    scanf ("%d", &userInputList[counter]);
    while (userInputList[counter] != -999) {
        
        printf ("Your number is %d\n", userInputList[counter]);
        
        counter = counter + 1; // go to the next index of the array
        
        if (counter >= size) {
            
            // code from professor troy assignment page
            tempArray = (int *) malloc ( size * 2 * sizeof(int) );
    
            tempArrayTwo = (int *) malloc ( size * 2 * sizeof(int) );
            
            // make more space for the array
            for (i=0; i < size; i++) {
                tempArray[i] = userInputList[i];
                tempArrayTwo[i] = duplicatedList[i];
            }
            
            free (userInputList);
            free (duplicatedList);
            
            userInputList = tempArray;
            duplicatedList = tempArrayTwo;
            
            // double size of array
            size = size * 2;
            
        }
        
        scanf ("%d", &userInputList[counter]);
    }
    
    // copy the array
    arrayCopy(userInputList, duplicatedList, counter);
    
    // sort the array
    sortArray(userInputList, counter);
    
    // read in values from user to see if the number can be found in the array
    printf ("Enter a number to see if it can be found and press -999 to stop\n");
    scanf ("%d", &userInput);
    while (userInput != -999) {
        
        // reset comparing numbers
        numComparisonsForLinear = 0;
        numComparisonsForBinary = 0;
        
        linearSearchPosition = linearSearch(duplicatedList, counter, userInput, &numComparisonsForLinear);
        
        binarySearchPosition = binarySearch(userInputList, counter, userInput, &numComparisonsForBinary);
        
        // check to see if the number is in the array
        if (linearSearchPosition == -1 && binarySearchPosition == -1) {
            printf ("The number %d could not be found\n", userInput);
        }
        
        if (linearSearchPosition != -1 && binarySearchPosition != -1) {
            printf ("The number %d is in the array!\n", userInput);
        }
        
        // number of comparisons..add code later...
        printf ("The number of comparisons for linear search is %d\n", numComparisonsForLinear);
        printf ("The number of comparisons for binary search is %d\n", numComparisonsForBinary);
        
         if (linearSearchPosition == -1 && binarySearchPosition == -1) {
                printf("\n"); // good space to read output
        }

        // location of the number in the array
        if (linearSearchPosition != -1 && binarySearchPosition != -1) {
            printf ("The number's position in the sorted array is %d\n", binarySearchPosition);
            printf ("The number's position in the un-sorted array is %d\n", linearSearchPosition);
            printf ("\n"); // good for eyes to read
        }
        
        scanf ("%d", &userInput);
        
    }
    
    return 0 ;
}
