#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <unistd.h>
#include <string.h>
#include "mymalloc.c"
#ifndef mymalloc
#include "mymalloc.h"
 
#define MEMSIZE 4096
#define HEADERSIZE 8
#define OBJECTS 64
#define OBJSIZE (MEMSIZE / OBJECTS - HEADERSIZE)

int correctnessTesting1(){
    char *obj[OBJECTS];
    int i, j, errors = 0;
    // fill memory with objects
    for (i = 0; i < OBJECTS; i++) {
    obj[i] = malloc(OBJSIZE);
        }
// fill each object with distinct bytes
    for (i = 0; i < OBJECTS; i++) {
        memset(obj[i], i, OBJSIZE);
    }
// check that all objects contain the correct bytes
    for (i = 0; i < OBJECTS; i++) {
        for (j = 0; j < OBJSIZE; j++) {
            if (obj[i][j] != i) {
                errors++;
                printf("Object %d byte %d incorrect: %d\n", i, j, obj[i]
            [j]);
            }
            }
            }
            printf("%d incorrect bytes\n", errors);
            memset( memory, 0, MEMLENGTH*sizeof(double) ) ;
            return EXIT_SUCCESS;
        }

void correctnessTesting2(){
    void* ptr = malloc(4000); // this will allocate max memeory   
    free(ptr); // deallocates memory 
    malloc(4000); //if it didnt deallocate before then it would not be able to allocate another 4080 bits without error
    printf("No Error\n");
    memset( memory, 0, MEMLENGTH*sizeof(double) ) ;

}

void correctnessTesting3(){
    void* ptr1 = malloc(2000);  //mallocs 2000
    void* ptr2 = malloc(2000);  //mallocs 2000
  
    //frees on both of the pointers on top, without coalescing this would be 2 seperate 2000 bytes freed blocks
    free(ptr1); 
    free(ptr2); 

    //calling malloc with 4000 bytes would not work unless the two 2000 byte blocks were coalesced
    malloc(4000);

    printf("No Error\n");
    memset( memory, 0, MEMLENGTH*sizeof(double) ) ;
    
}

void correctnessTesting4(){

    printf("  *Error 1: \n");

    malloc(4000);
    malloc(4000);
    memset( memory, 0, MEMLENGTH*sizeof(double) ) ;

    //This does not malloc the int x and therefore it can not free x because the address of x does not exist in memeory due to it not being allocated
    //Explation: Checks if a given pointer is within the range of memory allocated with malloc().
    //If the pointer falls outside this range, it reports an error, ensuring that myfree is only used with pointers that were obtained from malloc.
    printf("  *Error 2: \n");
    int x;
    free(&x);
    memset( memory, 0, MEMLENGTH*sizeof(double) ) ;

    //This frees the memory with an address that doesn't mark the beginning of an allocated block.
    //Explation: This test case helps ensure that your memory management system can accurately detect 
    //and report errors when trying to free memory that doesn't precisely match the allocated block's starting address.
    printf("  *Error 3: \n");
    char *f = malloc(sizeof(int)*2);
    free(f + 1);
    memset( memory, 0, MEMLENGTH*sizeof(double) ) ;

    //This testing if the memory is freed 2 times
    //Explation: This test case checks if you can free the same block of memory twice using the free() function,
    //,first it allocates memory for an array of 100 integers using the malloc() function and assigns the pointer p to it.
    //After that, it assigns the pointer q to the same memory block. Finally, it attempts to free the memory using free(p) and free(q) consecutively. 
    //The test is designed to see if the free() function can handle double-freeing the same memory and whether it produces any errors or warnings.
    printf("  *Error 4: \n");
    int *p = malloc(sizeof(int)*100);
    int *q = p;
    free(p);
    free(q);
    memset( memory, 0, MEMLENGTH*sizeof(double) ) ;
   

}
  






int main(int argc, char *argv[]){
    printf("Test result for correctnessTesting1(): \n \n");
    correctnessTesting1();
    printf(" \nTest result for correctnessTesting2(): \n \n");
    correctnessTesting2();
    printf("\nTest result for correctnessTesting3(): \n \n");
    correctnessTesting3();
    printf(" \nTest result for correctnessTesting4(): \n \n");
    correctnessTesting4();
}





#endif