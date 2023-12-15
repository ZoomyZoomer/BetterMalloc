#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <unistd.h>
#include "mymalloc.c"
#include <sys/time.h>
#include <time.h>

static struct timespec start, end;
static double timeTaken = 0;

void test1() {
    

    for (int k = 0; k < 50; k++) {
        clock_gettime(CLOCK_MONOTONIC, &start);

        for (int i = 0; i < 120; i++) { // Mallocs a 1 byte object and immediately frees it
            free(malloc(1));
        }

        clock_gettime(CLOCK_MONOTONIC, &end);

        double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;

        timeTaken += time_taken;
    }

    printf("Completed test1() with an average runtime of: %fms\n", (timeTaken * 1000 / 50.0));
    timeTaken = 0;
}

void test2() {

    char *ptrArray[120];  // Array to store 120 pointers
    

    for (int k = 0; k < 50; k++){

        clock_gettime(CLOCK_MONOTONIC, &start);

        

        for(int i = 0; i < 120; i++) {
            ptrArray[i] = malloc(1);  // Allocate 1 byte of memory and store the address
        }

        for(int i = 0; i < 120; i++) {
            free(ptrArray[i]);  // Release the memory
        }

        clock_gettime(CLOCK_MONOTONIC, &end);

        double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;

        timeTaken += time_taken;

        

    }

    printf("Completed test2() with an average runtime of: %fms \n", (timeTaken * 1000 / 50.0));
    timeTaken = 0;


   // Check if memory is cleared
}

void test3(){

    char* ptrArray[120];

    

for (int k = 0; k < 50; k++){

    clock_gettime(CLOCK_MONOTONIC, &start);
    
    // Initialize all elements to 0
    for (int p = 0; p < 120; p++){
        ptrArray[p] = 0;                              
    }

    void freeObj(){
        for (int j = 0; j < 120; j++){
            if (ptrArray[j] != 0){
                free(ptrArray[j]);
                ptrArray[j] = 0;
                break;
            }
        }
    }

    // Switch between malloc() and free()

    for (int i = 0; i < 120; i++){

        int randomNum = (rand() % 2);
        
        if (randomNum == 0){
            ptrArray[i] = malloc(1);
        } else {
            freeObj();
        }

    }


    // Free remaining pointers

    for (int i = 0; i < 120; i++){
        if(ptrArray[i] != 0){
            free(ptrArray[i]);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;

    timeTaken += time_taken;

}

printf("Completed test3() with an average runtime of: %fms \n", (timeTaken * 1000 / 50.0));
timeTaken = 0;

    

}

void test4(){

    // Merging adjacent memTest



    for (int k = 0; k < 50; k++){

        clock_gettime(CLOCK_MONOTONIC, &start);

        for (int i = 0; i < 120; i++){

            void* ptr1 = malloc(1000);
            void* ptr2 = malloc(1000);

            free(ptr2);
            free(ptr1);

        }

        clock_gettime(CLOCK_MONOTONIC, &end);

        double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;

        timeTaken += time_taken;

    }

    printf("Completed test4() with an average runtime of: %fms\n\n", (timeTaken * 1000.0) / 50.0);
    timeTaken = 0;

    


    

}

void test5(){


    // Alternate randomly between throwing a random error, and proper malloc + free call
    
    

    for (int k = 0; k < 50; k++){

        clock_gettime(CLOCK_MONOTONIC, &start);

        

        
        

            void mallocAndFree(){

                int randomByteNum = ((rand() % 100) + 1);

                void* ptr = malloc(randomByteNum);

                free(ptr);

        } 

        void throwError(){

            int randomError = (rand() % 3);

            if (randomError == 0){

                // Calling free with an address that was not allocated

                int x;
                free(&x);  

            } else if (randomError == 1){

                // Calling free with an address that is not at the start of the data block

                int *p = malloc(sizeof(int)*2);
                free(p + 1);

            } else {

                // Calling free on an already freed pointer

                int *p = malloc(sizeof(int)*100);
                int *q = p;
                free(p);
                free(q);

            }

        }

            for (int i = 0; i < 1; i++){

                int randomNum = (rand() % 2);

                if (randomNum == 0){
                    mallocAndFree();
                } else {
                    throwError();
                }

            }

            clock_gettime(CLOCK_MONOTONIC, &end);
            double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;

            timeTaken += time_taken;

    }

    // can't show because std was closed
    printf("Completed test5() with an average runtime of: %fms \n \n", (timeTaken * 1000.0) / 50.0);
    timeTaken = 0;

    

}



int main(int argc, char *argv[]){

    test1();
    test2();
    test3();
    test4();
    test5();

}