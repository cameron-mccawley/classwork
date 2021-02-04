/* CS261- HW1 - Program2.c*/
/* Name: Cameron McCawley
 * Date:
 * Solution description:
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>
#include <assert.h>

struct student{
	char initials[2];
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
     struct student *students = malloc(10 * sizeof(struct student));
     assert(students != NULL);
     /*return the pointer*/
     return students;
}

void generate(struct student* students){
     /*Generate random initials and scores for ten students.
	The two initial letters must be capital and must be between A and Z. 
	The scores must be between 0 and 100*/
    int i;
    for(i = 0; i < 10; i++){
        students[i].initials[0] = rand() % 26 + 'A';
        students[i].initials[1] = rand() % 26 + 'A';
        students[i].score = rand() % 101;
    }
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              1. Initials  Score
              2. Initials  Score
              ...
              10. Initials Score*/
    int i;
    for(i = 0; i < 10; i++){
        printf("%d. %c%c  %d\n", i + 1, students[i].initials[0], students[i].initials[1], students[i].score);
    }
}

void summary(struct student* students){
    /*Compute and print the minimum, maximum and average scores of the ten students*/
    int minimum = students[0].score;
    int maximum = students[0].score;
    int sum = students[0].score;
    double average;
    int i;
    for(i = 1; i < 10; i++){
        if(students[i].score < minimum){
            minimum = students[i].score;
        }else if(students[i].score > maximum){
            maximum = students[i].score;
        }
        sum += students[i].score;
    }
    average = (double) sum / 10;
    printf("Minimum: %d\nMaximum: %d\nAverage: %g\n", minimum, maximum, average);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
    free(stud);
}

int main(){
    struct student* stud = NULL;
    srand(time(0));
    /*call allocate*/
    stud = allocate();
    /*call generate*/
    generate(stud);
    /*call output*/
    output(stud);
    /*call summary*/
    summary(stud);
    /*call deallocate*/
    deallocate(stud);
    return 0;
}
