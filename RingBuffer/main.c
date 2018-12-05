//
//  main.c
//  RingTest
//
//  Created by Luca Pascarella on 9/4/18.
//  Copyright © 2018 Luca Pascarella. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Test1.h"
#include "RingBuffer.h"

#define SPACE_SIZE      17

void printb(uint8_t *buf, size_t size);
void testLinearSpaces(RING_DATA *ring);

int main(int argc, const char * argv[]) {
    uint8_t *ptr, *ptr1, *buf, dynBuf[SPACE_SIZE];
    size_t i, toWrite, free, full, size, written, readable;
    RING_DATA *ring;
    
    printf("Start RingBuffer\n\n");
    
    printf("Test creation and destroing: %c\n", Test_CreateAndDestroyRing()?'Y':'N');
    printf("Test size: %c\n", Test_Size()?'Y':'N');
    printf("Test free space: %c\n", Test_FreeSpace()?'Y':'N');
    printf("Test full space: %c\n", Test_FullSpace()?'Y':'N');
    printf("Test fill all: %c\n", Test_FillAll()?'Y':'N');
    
    // This is usefull for debugging purpose when ring is rounded down than buffer size,
    // After tests not used space must contain the assigned character
    memset(dynBuf, 'X', SPACE_SIZE);
    
    dynBuf[SPACE_SIZE-1] = 'X';
    if ((ring = RING_InitBuffer(dynBuf, SPACE_SIZE)) == NULL){
        printf("Failed to allocate\n");
        return -1;
    }
    assert(ring != NULL);
    assert(dynBuf[SPACE_SIZE-1] == 'X');
    
    // testLinearSpaces(ring);
    
    // Test size
    size = RING_GetBufferSize(ring);
    printf("Rounded down from %d to %ld\n", SPACE_SIZE, size);
    //assert(size == 16);

    // Test free and full spece
    printf("\n");
    free = RING_GetFreeSpace(ring);
    full = RING_GetFullSpace(ring);
    printf("Free space: %ld. Full space: %ld\n", free, full);
    printf("Free linear space: %ld. Full linear space: %ld\n", RING_GetFreeLinearSpace(ring), RING_GetFullLinearSpace(ring));
    
    // Test add buffer
    printf("\n");
    char *str = "0123456789A"; //defghjklmnopqrst";
    // written = RING_AddBuffer(ring, (uint8_t*)str, (uint32_t)strlen(str));
    buf = RING_AddBufferDirectly(ring, &toWrite, (uint32_t)strlen(str));
    for(i=0; i < toWrite; i++)
        buf[i] = str[i];
    written = toWrite;
    printf("Written: %ld of %ld, Free space: %ld, Full space: %ld\n", written, strlen(str), RING_GetFreeSpace(ring), RING_GetFullSpace(ring));
    printf("Free linear space: %ld. Full linear space: %ld\n", RING_GetFreeLinearSpace(ring), RING_GetFullLinearSpace(ring));
    
    // Test add buffer
    printf("\n");
    char *str1 = "BCDEFGH"; //defghjklmnopqrst";
    written = RING_AddBuffer(ring, (uint8_t*)str1, (uint32_t)strlen(str1));
    printf("Written: %ld of %ld, Free space: %ld, Full space: %ld\n", written, strlen(str1), RING_GetFreeSpace(ring), RING_GetFullSpace(ring));
    printf("Free linear space: %ld. Full linear space: %ld\n", RING_GetFreeLinearSpace(ring), RING_GetFullLinearSpace(ring));
    
    // Test read
    printf("\n");
    printf("Free space: %ld. Full space: %ld\n", RING_GetFreeSpace(ring), RING_GetFullSpace(ring));
    ptr1 = malloc(SPACE_SIZE);
    buf = RING_GetBufferDirectly(ring, &readable, SPACE_SIZE/2);
    for(i=0; i<readable; i++)
        ptr1[i] = buf[i];
    printf("Readable: %ld, ", readable);
    printb(ptr1, readable);
    
    char *str2 = "KZ";
    written = RING_AddBuffer(ring, (uint8_t*)str2, (uint32_t)strlen(str2));
    
    printf("Written: %ld of %ld, Free space: %ld, Full space: %ld\n", written, strlen(str2), RING_GetFreeSpace(ring), RING_GetFullSpace(ring));
    printf("Free linear space: %ld. Full linear space: %ld\n", RING_GetFreeLinearSpace(ring), RING_GetFullLinearSpace(ring));
    
    buf = RING_GetBufferDirectly(ring, &readable, SPACE_SIZE);
    for(i=0; i<readable; i++)
        ptr1[i] = buf[i];
    printf("Readable: %ld, ", readable);
    printb(ptr1, readable);
    //free(ptr1);
    printf("Free space: %ld. Full space: %ld\n", RING_GetFreeSpace(ring), RING_GetFullSpace(ring));
    printf("Free linear space: %ld. Full linear space: %ld\n", RING_GetFreeLinearSpace(ring), RING_GetFullLinearSpace(ring));
   
    if (dynBuf[SPACE_SIZE-1] == 'X')
        printf("Ended correctly\n");
    else
        printf("Ended with errors\n");
    
    return 0;
}

void testLinearSpaces(RING_DATA *ring) {
    size_t free, full;
    
    free = RING_GetFreeSpace(ring);
    full = RING_GetFullSpace(ring);
    printf("Free space: %ld. Full space: %ld\n", free, full);
    
    free = RING_GetFreeLinearSpace(ring);
    full = RING_GetFullLinearSpace(ring);
    printf("Free linear space: %ld. Full linear space: %ld\n", free, full);
}

void printb(uint8_t *buf, size_t size) {
    size_t i;
    
    printf("'");
    for(i=0; i<size; i++)
        printf("%c", buf[i]);
    printf("'\n");
}
