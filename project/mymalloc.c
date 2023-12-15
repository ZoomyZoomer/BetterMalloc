
#include <math.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#ifndef mymalloc
#include "mymalloc.h"
#include <stdbool.h>
#define MEMLENGTH 512
static double memory[MEMLENGTH];

#define ROUNDUP8(x) (((x) + 7 ) & (-8))



void *mymalloc(size_t size, char *file, int line) {
    if (size == 0) {
        printf("%s", "Error: can't allocate 0 bytes \n");
    }

    if (size > MEMLENGTH * sizeof(double)) {
        printf("%s %zu %s ", "Error: can not allocate ", size, " bytes \n");
    }

    size = ROUNDUP8(size);
 
    char* res = NULL;                  
    char* heapStart = (char*)memory;   
    int currPos = 0;

    while (currPos <= MEMLENGTH * sizeof(double) - size - (2 * sizeof(int))) {
        int chunkSize = *(int*)(heapStart);                  // Cast to int when accessing chunkSize
        int isFree = *(int*)(heapStart + sizeof(int));       // Cast to int when accessing isFree

        if (chunkSize == 0 && isFree == 0) {                 // First-ever initialization
            *(int*)(heapStart) = size + (2 * sizeof(int));  // Cast to int when modifying chunkSize
            *(int*)(heapStart + sizeof(int)) = 1;           // Cast to int when modifying isFree
            res = (char*)(heapStart + 2 * sizeof(int));
            *(int*)(heapStart + size + 2 * sizeof(int)) = MEMLENGTH * sizeof(double) - (size + 2 * sizeof(int));
            //printf("%s %zu %s", "FIRST allocation of: ", size + 8, " bytes |  \n");
            return res;
        }

        if (isFree == 0 && chunkSize >= size + 8) {
            *(int*)(heapStart) = size + (2 * sizeof(int));
            *(int*)(heapStart + sizeof(int)) = 1;
            res = (char*)(heapStart + 2 * sizeof(int));
             //printf("%s %zu %s", "NEW allocation of: ", size + 2 * sizeof(int), " bytes -> ");
            if (*(int*)(heapStart + size + 2 * sizeof(int)) == 0) {
                *(int*)(heapStart + size + 2 * sizeof(int)) = chunkSize - (size + 2 * sizeof(int));
                //printf("%s %zu %s", "Created chunk of: ", chunkSize - (size + 2 * sizeof(int)), " bytes | \n");
            }
            return res;
        }

        if (isFree == 1 || chunkSize < size + 2 * sizeof(int)) {
            currPos += chunkSize;
            heapStart = (char*)heapStart + chunkSize; 
        }
    }

    printf("Error: Not enough memory at %s:%d\n", file, line);
    return NULL;
}

void myfree(void *ptr, char *file, int line) {

    if (ptr == NULL){
        printf("Error: Pointer not in heap or out of bounds at %s:%d\n", file, line);
        return;
    }

    // Define a flag to track if the pointer was already freed
    int doubleFree = 0;
    
    char* heapStart = (char*) memory; 
    int currPos = 0;
    int flag = 0;

    if (ptr >= (void*)memory && ptr < (void*)((char*)memory + MEMLENGTH * sizeof(double))) {
        flag = 1;
    }

    if (!flag) {
        printf("Error: myfree called with an address not obtained from malloc at %s:%d\n", file, line);
        return;
    }


    while(currPos < MEMLENGTH * sizeof(double)){

        int chunkSize = *(int*)heapStart;
        int isFree = *(int*)(heapStart + sizeof(int));

        char* currBlock = (char*)heapStart + sizeof(double);
        char* nextBlockChunkSize = NULL;
        char* nextBlockFree = NULL;
        int tempChunk = 0;



        if ((char*)(currBlock + chunkSize) == (char*)ptr && isFree == 0){    // if the next block is ptr and currBlock is free...

            nextBlockChunkSize = ((char*)heapStart + chunkSize);
            nextBlockFree = ((char*)heapStart + chunkSize + sizeof(int));
            
            // we want to merge the blocks
            
            tempChunk = *(int*)nextBlockChunkSize;

            *(int*)(heapStart) = chunkSize + tempChunk;


            // now erase the evidence

            *(int*)nextBlockChunkSize = 0;
            *(int*)nextBlockFree = 0;

            //printf("Merged Blocks adjacent  |  \n");

            // Lets check if the next block AFTER the merge is also free, if so, we merge it too

            int chunkSize = *(int*)heapStart;       // Lets update chunksize

            nextBlockChunkSize = ((char*)heapStart + chunkSize);
            nextBlockFree = ((char*)heapStart + chunkSize + sizeof(int));

           

            if (*(int*)nextBlockFree == 0){

                // we want to merge the blocks

                tempChunk = *(int*)nextBlockChunkSize;

                *(int*)(heapStart) = chunkSize + tempChunk;

                // now erase the evidence

                *(int*)nextBlockChunkSize = 0;
                
            //printf("Merged AFTER merge  |  \n");

            }

            return;

        }


        if (currBlock == (char*)ptr){           // If the current Block is ptr...
            if(isFree == 0 ){
           
                printf("Error: Cannnot free an already freed pointer at %s:%d\n", file, line);
                return;

            }
                // check if next block is free
            nextBlockChunkSize = ((char*)heapStart + chunkSize);
            nextBlockFree = ((char*)heapStart + chunkSize + sizeof(int));

            if (*nextBlockFree == 0){

                // we want to merge the blocks

                tempChunk = *(int*)nextBlockChunkSize;

                *(int*)(heapStart) = chunkSize + tempChunk; // change chunk size with the merge
                *(int*)(heapStart + sizeof(int)) = 0;       // free ptr

                // now erase the evidence
                *(int*)nextBlockChunkSize = 0;
                *(int*)nextBlockFree = 0;

            } 




            *(int*)(heapStart + sizeof(int)) = 0;  // set ptr free

            //printf("freed %d bytes \n", chunkSize);
            return;
        }

        currPos += chunkSize;
        heapStart = (char*)(heapStart + chunkSize);

    }


    printf("Pointer is not referencing a valid data block at %s:%d\n", file, line);
    return;

}

#endif