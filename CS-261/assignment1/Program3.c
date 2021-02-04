/* CS261- HW1 - Program3.c*/
/* Name: Cameron McCawley
 * Date:
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

void sort(int* number, int n){
     /*Sort the array of integeres of length n*/
     int i, j, key;
     for(i = 1; i < n; i++){
         key = number[i];
         j = i - 1;

         while(j >= 0 && number[j] > key){
             number[j + 1] = number[j];
             j = j - 1;
         }
         number[j + 1] = key;
     }     
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    int *array = NULL;
    int i;

    srand(time(0));
    /*Allocate memory for an array of n integers using malloc.*/
    array = malloc(sizeof(int)*n);
    /*Fill this array with random numbers, using rand().*/
    for(i = 0; i < n; i++){
        array[i] = rand() % 101;
    }
    /*Print the contents of the array.*/
    for(i = 0; i < n; i++){
        printf("%d, ", array[i]);
    }
    printf("\n\n");
    /*Pass this array along with n to the sort() function of part a.*/
    sort(array, n);
    /*Print the contents of the array.*/    
    for(i = 0; i < n; i++){
        printf("%d, ", array[i]);
    }
    printf("\n");
    free(array);
    return 0;
}
