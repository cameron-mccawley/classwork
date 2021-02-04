/* CS261- HW1 - Program4.c*/
/* Name: Cameron McCawley
 * Date:
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

struct student{
	char initials[2];
	int score;
};

void sort(struct student* students, int n){
     /*Sort n students based on their initials*/
     int i, j;
     struct student key;
     for(i = 1; i < n; i++){
         key = students[i];
         j = i - 1;

         while(j >= 0 && strcmp(students[j].initials, key.initials) > 0){
             students[j + 1] = students[j];
             j = j - 1;
         }
         students[j + 1] = key;
     }     
}

int main(){
    /*Declare an integer n and assign it a value.*/
    int n;
    int i;
    struct student *students = NULL;
    srand(time(NULL));
    printf("Enter number of students:");
    scanf("%d", &n);
    assert(n >= 0);
    /*Allocate memory for n students using malloc.*/
    students = (struct student *) malloc(sizeof(struct student)*n); 
    assert(students != NULL);
    /*Generate random IDs and scores for the n students, using rand().*/
    for(i = 0; i < n; i++){
        students[i].initials[0] = rand() % 26 + 'A';
        students[i].initials[1] = rand() % 26 + 'A';
        students[i].score = rand() % 101;
    }
    /*Print the contents of the array of n students.*/
    for(i = 0; i < n; i++){
        printf("%d. %c%c  %d\n", i + 1, students[i].initials[0], students[i].initials[1], students[i].score);
    }
    /*Pass this array along with n to the sort() function*/
    sort(students, n);
    /*Print the contents of the array of n students.*/
    for(i = 0; i < n; i++){
        printf("%d. %c%c  %d\n", i + 1, students[i].initials[0], students[i].initials[1], students[i].score);
    }
    free(students);
    return 0;
}
