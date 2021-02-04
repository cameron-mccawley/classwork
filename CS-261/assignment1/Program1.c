/* CS261- HW1 - Program1.c*/
/* Name: Cameron McCawley  
 * Date: 
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){
    /* Increment a */
    *a += 1;
    /* Decrement  b */
    *b -= 1;
    /* Assign a-b to c */
    c = *a - *b;
    /* Return c */
    return c;
}

int main(){
    /* Declare three integers x,y and z and initialize them randomly to values in [0,10] */
    int x, y, z, c;
    srand(time(0));
    x = rand() % 11;
    y = rand() % 11;
    z = rand() % 11;
    /* Print the values of x, y and z */
    printf("x = %d, y = %d, z = %d\n", x, y, z);
    /* Call foo() appropriately, passing x,y,z as parameters */
    c = foo(&x, &y, z);
    /* Print the values of x, y and z */
    printf("x = %d, y = %d, z = %d\n", x, y, z);
    /* Print the value returned by foo */
    printf("Value returned by foo() = %d\n", c);
    /* Is the return value different than the value of z?  Why? */
    printf("z is different than the value returned by foo() because the value of z was copied when passed to foo(),\n"
            "so any changes to it in foo() would not affect the original variable\n");

    return 0;
}
    
    
